# -*- coding: utf-8 -*-
"""
Created on Thu Feb  9 15:03:01 2017

@author: root
"""
import os
import matplotlib.pyplot as plt
import numpy as np
from collections import defaultdict
from matplotlib import font_manager
import math
from optparse import OptionParser

def getKey(in_list):
        return in_list[0]
        
def calculate_size_time(in_list,max_size):
    #print 'call calculate_size_time'
    size_time = defaultdict()
    size_list = []
    for i in range(0,int(math.log(max_size,2))+1):  #size in KB
        size_list.append(math.pow(2,i))

    i = 0
    sum_time = 0
    n = 0
    #print size_list
    for length in size_list:
        while i<len(in_list) and in_list[i][0]<=length:
            #print l[0:]
            for time in in_list[i][1:]:
                if time>0:
                    sum_time = sum_time + time
                    n = n + 1
            i = i + 1
        #print length,': ', n                
        if n > 0:
            size_time.setdefault(str(length),sum_time/float(n))
        else:
            size_time.setdefault(str(length),0)
        n = 0
        sum_time = 0
                            
    return size_list, size_time
        
def sortDict_2list(in_dict,fname):
    #print 'call sortDict_2list'
    in_list = []
    avg_size = 0
    max_size = 0
    for a in in_dict.keys():
        #print a
        size = a
        avg_size = avg_size + size
        newlist = []
        for k in in_dict[a]:
            newlist.append(k)
        newlist.sort()
        newlist.insert(0,size)
        in_list.append(newlist)  
    #print (in_list[0])            
    size = in_list[0][0]
    in_list.sort(key=getKey)    
    #print (in_list[len(in_list)-1])
    if len(in_list)>0:
        max_size = in_list[len(in_list)-1][0]
        avg_size = avg_size / float(len(in_list))
    #print 'max_size:' + str(max_size)
    else:
        max_size = 0
        avg_size = 0
#    f=open('size_latency_'+fname+'.txt','w')
#    for size in in_list:
#        print(str(size[0][0]),file=f)
#        for item in size[1:]:
#            print(str(item[0])+', '+str(item[1])+': '+str(item[2]),file=f)
#        print('\n',file=f)
    #print (in_list[len(in_list)-1])
    return avg_size,max_size,in_list
        
def plot_bar(x_labels,bars, names,color, hatch,fileName) :
    bars_val = []
    for i in range(len(bars)):       
        bars_val.append([])
    
    xtick=[]
    for key in x_labels:
        xtick.append(int(key))
        for i in range(len(bars_val)):
            bars_val[i].append(bars[i][str(key)]/float(1000))
        
 
    N = len(x_labels)
    ind = np.arange(N)  # the x locations for the links
    width = 0.4        # the width of the bars
    #k = len(bars)
    for i in range(N):
        ind[i] = i*5*width
    print(ind[0])
    print(ind[1])
    print(ind[2])
    
    fig, ax = plt.subplots()
    plt.gcf().subplots_adjust(bottom=0.2)
    ticks_font = font_manager.FontProperties(family='sans-serif', style='normal',\
                size=20, weight='normal', stretch='normal')
    for label in ax.get_xticklabels():
        label.set_fontproperties(ticks_font)

    for label in ax.get_yticklabels():
        label.set_fontproperties(ticks_font)   
        
    rects=[]
    for i in range(len(bars_val)):
        rects.append(ax.bar(ind +i*width, bars_val[i][0:N], width, color=color[i],hatch=hatch[i],log=True))
        
            
    # add some text for labels, title and axes ticks
    ax.set_ylabel('Latency (s)',fontsize=18)
    ax.set_xlabel('average size (KB)',fontsize=18)
    #ax.set_yscale('log')
    #ax.set_title('Average latency in different size range')
    ax.set_xticklabels(xtick[0:N], rotation=90)
    ax.set_xticks(ind + len(bars)*width/2)
    
    ax.legend(rects, names,fontsize=18)
    plt.savefig(outfolder + fileName)
    plt.clf()   

def plot_size_time(picn_hit_size_time, local_size_time, miss_size_time, web_size_time):

    avg_size_picn,maxsize_picn,in_list_picn = sortDict_2list(picn_hit_size_time,'picn_hit')
    avg_size_web,maxsize_web,in_list_web = sortDict_2list(web_size_time,'web')
    avg_size_miss,maxsize_miss,in_list_miss = sortDict_2list(miss_size_time,'miss')
    #avg_size_local,maxsize_local,in_list_local = sortDict_2list(local_size_time,'local')
    maxsize = max([maxsize_picn,maxsize_web,maxsize_miss])
    
    size_list_picn, size_avgTime_picn = calculate_size_time(in_list_picn, maxsize)
    _,size_avgTime_web = calculate_size_time(in_list_web, maxsize)
    #_,size_avgTime_local = calculate_size_time(in_list_local, maxsize)
    _,size_avgTime_miss = calculate_size_time(in_list_miss, maxsize)
       
    
    fname = outfolder + 'size_time.txt'
    with open(fname, 'w') as fout:
        for size in size_list_picn:
            slen = str(size)
            fout.write ('size: '+slen + '\n')
            fout.write ( 'picn: ('+ str(size_avgTime_picn[slen]) +' )\n')
            fout.write ( 'miss: ('+ str(size_avgTime_miss[slen])+')\n')
            fout.write ( 'web: ('+ str(size_avgTime_web[slen])+')\n')
            
    fout.close()
    
    plot_bar(size_list_picn,[size_avgTime_picn,size_avgTime_miss, size_avgTime_web],
                      ['hit in peers','miss in peers','without PICN'],
                        ['g','r','0.75'],['///','...',''],'size_time.pdf') 
                        
def cdf(vector, max_speed):
    max_size = 1#Mb/s
    interval_num = float(100)
    x = np.arange(0,max_size,max_size/interval_num)
    end = x[len(x)-1]
    
    max_size = 5#Mb/s
    interval_num = float(100)
    step = (max_size-end)/interval_num
    xx = np.arange(end+step,max_size,step)
    x = np.append(x,xx)
    end = x[len(x)-1]
    
    max_size = 10#Mb/s
    interval_num = float(100)
    step = (max_size-end)/interval_num
    xx = np.arange(end+step,max_size,step)
    x = np.append(x,xx)
    end = x[len(x)-1]
    
    max_size = max_speed
    interval_num = float(100)
    step = (max_size-end)/interval_num
    xx = np.arange(end+step,max_size,step)
    x = np.append(x,xx)
    
    y = []
    y.append(0)
    for i in range(len(x)-1):
        y.append(len([speed for speed in vector if speed>x[i] and speed<=x[i+1]]))
    
    cdf = np.cumsum(y)/float(np.sum(y))
    
    return cdf, x
                        
def plot_speed_cdf(picn,local,miss,web):
    picn_cdf,picn_speed = cdf(picn,max(picn))
    #local_cdf,local_speed = cdf(local,max(local))
    miss_cdf,miss_speed = cdf(miss,max(miss))
    web_cdf,web_speed = cdf(web,max(web))
   
    #print 'plotting speed cdf...'
    plt.ion()
    fig, ax = plt.subplots()
    plt.gcf().subplots_adjust(bottom=0.15)
    ticks_font = font_manager.FontProperties(family='sans-serif', style='normal',\
                size=20, weight='normal', stretch='normal')
    for label in ax.get_xticklabels():
        label.set_fontproperties(ticks_font)

    for label in ax.get_yticklabels():
        label.set_fontproperties(ticks_font)   
    n = len(picn_speed)
    diag_picn = ax.plot(picn_speed[0:n],picn_cdf[0:n],color='g',linestyle='--',marker='',linewidth = 3,label='hit in peers')
    #diag_local = ax.plot(local_speed[0:n],local_cdf[0:n],color='b',linestyle='-.',marker='',linewidth = 3,label='hit in local cache')
    diag_web = ax.plot(web_speed[0:n],web_cdf[0:n],color='r',marker='',linestyle=':',linewidth = 3,label='without picn')
    diag_miss = ax.plot(miss_speed[0:n],miss_cdf[0:n],color='k',marker='',linestyle='-',linewidth = 3,label='miss in picn')
    ax.set_xscale('log')
    ax.set_xlabel('Transfer rate (Mb/s)',fontsize=18)
    ax.set_ylabel('CDF of transfer rate',fontsize=18)
    ax.legend((diag_picn[0],diag_miss[0],diag_web[0]),('hit in peers','miss in peers','without PICN'),loc=0,fontsize=18) 
    fig.savefig(outfolder + 'PICN_CDF.pdf',format='PDF',dpi=5)
  
#def calculate_size_speed(size_time,max_size):
#    interval_num = 5
#    sizes = np.arange(0,max_size,max_size/interval_num)
#    i=0
#    for len in sizes:
#        while(i<len(size_time) and )    
#    
#def table_size_speed(picn_size_time, local_size_time, miss_size_time, web_size_time):
#    max_size = min([max(picn_size_time),max(local_size_time),max(miss_size_time),max(web_size_time))
#    sizes,picn_size_speed = calculate_size_speed(picn_size_time,max_size)


if __name__=='__main__':
    logNum = str('')
    #aliveProb = 100
    parser = OptionParser()
    parser.add_option("-p", "--path", dest="log_files_path",
                      help="Path to the folder containing the log files of all the clients")
    (options, args) = parser.parse_args()
    logfolder = (options.log_files_path) if options.log_files_path else './Logs'
    outfolder = logfolder+'/Results/'
    if not os.path.exists(outfolder):
       os.makedirs(outfolder)
       
    web_size = 0
    picn_size = 0
    local_size = 0
    miss_size = 0
    
    picn_size_time=defaultdict()
    web_size_time=defaultdict()
    miss_size_time=defaultdict()
    local_size_time=defaultdict()
    
    speed_picn=[]
    speed_web=[]
    speed_miss=[]
    speed_local=[]
    
    
    for filename in os.listdir(logfolder):
        if os.path.isdir(logfolder + '/' + filename):
            continue
        f = open(logfolder + '/' + filename)
        print (filename)
        ## Read the first line 
        line = f.readline()
        while line:
            fields = line.split()
            if fields[0]=='HTTP':
                if fields[1]=='.non':
                    size = int(fields[2])
                    time = int(fields[3])
                    web_size = web_size + size
                    web_size_time.setdefault(size/float(1000),[]).append(time)
                    speed_web.append(size*8/float(time*1000))
                else:
                    size = int(fields[3])
                    time = int(fields[4])
                    miss_size = miss_size + size
                    miss_size_time.setdefault(size/float(1000),[]).append(time)
                    speed_miss.append(size*8/float(time*1000))
                    
            elif fields[0]=='PICN':
                size = int(fields[3])
                time = int(fields[4])
                picn_size = picn_size + size
                picn_size_time.setdefault(size/float(1000),[]).append(time)
                speed_picn.append(size*8/float(time*1000))
            elif fields[0]=='LPICN':
                size = int(fields[3])
                time = int(fields[4])
                local_size = local_size + size
                local_size_time.setdefault(size/float(1000),[]).append(time)
                speed_local.append(size*8/float(time*1000))
                
            line = f.readline()
            
    tot_size = miss_size + picn_size + local_size + web_size
    
    picn_hit=len(speed_picn)
    local_hit=len(speed_local)
    miss = len(speed_miss)
    web = len(speed_web)
    total_req = picn_hit + local_hit + miss + web 
    supported = picn_hit + local_hit + miss 
    
    with open(outfolder+'results.txt', 'w') as fout:
        fout.write('supported number of requests:'+str(supported))
        fout.write('\nHit ratio in peers:'+str(picn_hit/float(supported)))
        fout.write('\nHit ratio in local cache:'+str(local_hit/float(supported)))
        fout.write('\nTotal hit ratio:'+str((local_hit+picn_hit)/float(supported)))
        fout.write('\nTotal traffic:' + str(tot_size))
        
        fout.write('\nsaved external traffic:' + str(picn_size/float(tot_size)*100))
        fout.write('\nsaved external traffic (picn+local):' + str((picn_size+local_size)/float(tot_size)*100))
        fout.write('\nMaximum speed provides by peers:' + str(max(speed_picn)))
        fout.write('\nMaximum speed provides by local:' + str(max(speed_local)))
        fout.write('\nMaximum speed provides by main web servers when the requests miss in PICN:' + str(max(speed_miss)))
        fout.write('\nMaximum speed provides by main web servers:' + str(max(speed_web)))
        
    #table_size_speed(picn_size_time,local_size_time, miss_size_time,web_size_time)
    plot_size_time(picn_size_time,local_size_time, miss_size_time,web_size_time)
    plot_speed_cdf(speed_picn,speed_local,speed_miss,speed_web)
