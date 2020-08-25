"""i2c btw arduino and pi"""
import smbus
import time
import struct
"""end"""

'''Capturing'''
from time import sleep
from picamera import PiCamera
import os
'''end'''

'''Object detection'''
import cv2
import numpy as np
import glob
import random
'''end'''

'''Emailing'''
import smtplib
'''end'''

########################################set up
'''delay'''
time.sleep(10);
'''end'''

"""i2c btw arduino and pi"""
bus = smbus.SMBus(1)
address = 0x04
def get_data():
    return bus.read_i2c_block_data(address, 0);
def get_float(data_bytes,index):
    bytes = data_bytes[4*index:4*index+4]
    aux = bytearray(bytes)
    data_float=struct.unpack('<f',aux)[0]
    return data_float
"""end"""

'''Capturing'''
camera = PiCamera()
camera.resolution = (2592, 1944)
'''end'''

'''Object detection'''
# Load Yolo
net = cv2.dnn.readNet("yolov3_training_last.weights", "yolov3_testing.cfg")

# Name custom object
classes = ["fruitfly"]

# Images path
images_path = glob.glob(r"/home/pi/Desktop/yolo_custom_detection/Test_camera5MP/*.jpg")

layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]
colors = np.random.uniform(0, 255, size=(len(classes), 3))
'''end'''

'''Emailing'''
#Email Variables
SMTP_SERVER = 'smtp.gmail.com' #Email Server (don't change!)
SMTP_PORT = 587 #Server Port (don't change!)
GMAIL_USERNAME = 'msst2016_dong.pt@student.vgu.edu.vn' #change this to match your gmail account
GMAIL_PASSWORD = 'Vgumoi46'  #change this to match your gmail password
 
class Emailer:
    def sendmail(self, recipient, subject, content):
         
        #Create Headers
        headers = ["From: " + GMAIL_USERNAME, "Subject: " + subject, "To: " + recipient,
                   "MIME-Version: 1.0", "Content-Type: text/html"]
        headers = "\r\n".join(headers)
 
        #Connect to Gmail Server
        session = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        session.ehlo()
        session.starttls()
        session.ehlo()
 
        #Login to Gmail
        session.login(GMAIL_USERNAME, GMAIL_PASSWORD)
 
        #Send Email & Exit
        session.sendmail(GMAIL_USERNAME, recipient, headers + "\r\n\r\n" + content)
        session.quit
 
sender = Emailer()
 
sendTo = 'phamtdong0406@gmail.com'

'''end'''

#####################################action

"""i2c btw arduino and pi"""
x = 0
for x in range(10):
    data = get_data()
    print(str(get_float(data, 0))+" h")
    print(str(get_float(data, 1))+" m")
    print(str(get_float(data, 2))+" K")
    print(str(get_float(data, 3))+" lx")
    print(str(get_float(data, 4))+" V")
    print(str(get_float(data, 5))+" mA")
    print(str(get_float(data, 6))+" *C")
    print(str(get_float(data, 7))+" %")
    print(" ")
    time.sleep(1);
"""end"""

'''Capturing'''
sleep(3)
os.chdir ("/home/pi/Desktop/yolo_custom_detection/Test_camera5MP")

camera.capture('img.jpg')
'''end'''

'''object detection'''
#Number of fruitfly
#index = 0
# Insert here the path of your images
random.shuffle(images_path)
# loop through all the images
for img_path in images_path:
    # Loading image
    img = cv2.imread(img_path)
    img = cv2.resize(img, None, fx=0.4, fy=0.4)
    height, width, channels = img.shape

    # Detecting objects
    blob = cv2.dnn.blobFromImage(img, 0.00392, (416, 416), (0, 0, 0), True, crop=False)

    net.setInput(blob)
    outs = net.forward(output_layers)

    # Showing informations on the screen
    class_ids = []
    confidences = []
    boxes = []
    for out in outs:
        for detection in out:
            
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > 0.3:
                # Object detected
                print(class_id)
                center_x = int(detection[0] * width)
                center_y = int(detection[1] * height)
                w = int(detection[2] * width)
                h = int(detection[3] * height)
                
                # Rectangle coordinates
                x = int(center_x - w / 2)
                y = int(center_y - h / 2)

                boxes.append([x, y, w, h])
                confidences.append(float(confidence))
                class_ids.append(class_id)

    indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.5, 0.4)
    print(indexes)
    # Count fruitfly
    print('Number of fruitfly = '+str(len(indexes)))
    #index = indexes
'''
    font = cv2.FONT_HERSHEY_PLAIN
    for i in range(len(boxes)):
        if i in indexes:
            x, y, w, h = boxes[i]
            label = str(classes[class_ids[i]])
            color = colors[class_ids[i]]
            cv2.rectangle(img, (x, y), (x + w, y + h), color, 2)
            cv2.putText(img, label, (x, y + 30), font, 3, color, 2)
    
    img2 = cv2.resize(img, (820, 616))
    cv2.imshow("Image", img2)
    index = indexes
    #key = cv2.waitKey(0)#keep showing the window

cv2.destroyAllWindows()'''
'''end'''

'''send an email'''
print("emailing")

emailSubject = "Alert in Smart fruitfly trap"

#"This is a test of my Emailer Class"
emailContent = "Number of fruitfly = "+str(len(indexes))+"<br>"+"Light: "+str(round(get_float(data, 2),0))+" K, "+str(round(get_float(data, 3),0))+" lux, <br>"+"Battery voltage: "+str(round(get_float(data, 4),2))+" V, <br>"+"Solar pannel current: "+str(round(get_float(data, 5),2))+" mA, <br>"+"Temperature: "+str(round(get_float(data, 6),1))+" *C, <br>"+"Humidity: "+str(round(get_float(data, 7),1))+" %. "

#Sends an email to the "sendTo" address with the specified "emailSubject" as the subject and "emailContent" as the email content.
sender.sendmail(sendTo, emailSubject, emailContent)
'''end'''

'''Safe shutdown'''
time.sleep(10);
import Safe_shutdown
'''end'''
        


