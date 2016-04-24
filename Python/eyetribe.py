from peyetribe import EyeTribe
import time
import pickle
import json
from pythonosc import osc_message_builder
from pythonosc import udp_client
import argparse

tracker = EyeTribe()
tracker._hbinterval = 5
tracker.connect()
n = tracker.next()

parser = argparse.ArgumentParser()
parser.add_argument("--ip", default="127.0.0.1",help="The ip of the OSC server")
parser.add_argument("--port", type=int, default=12345,help="The port the OSC server is listening on")
args = parser.parse_args()

client = udp_client.UDPClient(args.ip, args.port)


print("eT;dT;aT;Fix;State;Rwx;Rwy;Avx;Avy;LRwx;LRwy;LAvx;LAvy;LPSz;LCx;LCy;RRwx;RRwy;RAvx;RAvy;RPSz;RCx;RCy")
frame = []
totalData = []
attributes = "eT;dT;aT;Fix;State;Rwx;Rwy;Avx;Avy;LRwx;LRwy;LAvx;LAvy;LPSz;LCx;LCy;RRwx;RRwy;RAvx;RAvy;RPSz;RCx;RCy".split(';')

tracker.pushmode()
count = 0
while True: #count < 60:
    n = tracker.next()
    print(n)
    frame = str(n).split(';')
    frameDict = {}
    for i in range(len(frame)):
    	frameDict[attributes[i]]=frame[i]
    totalData.append(frameDict)
    #print(n)
    count += 1
    msg = osc_message_builder.OscMessageBuilder(address = "/avXY")
    msg.add_arg(frameDict['Avx'])
    msg.add_arg(frameDict['Avy'])    
    print("{}, {}".format(frameDict['Avx'],frameDict['Avy']))
    msg = msg.build()
    client.send(msg)    
    #time.sleep(0.5)
    


tracker.pullmode()

tracker.close()
print ('------------------------------')
#print totalData[0]['RCy']
#pickle.dump(totalData, open('eyeData.p', 'wb'))
dataLoaded = pickle.load(open('eyeData.p', 'rb'))

#print dataLoaded
print(totalData)
jsonData = json.dumps(totalData)
fileWriter = open('eyeData.json', 'w')
fileWriter.write(jsonData)