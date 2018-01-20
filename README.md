# Project Arduino
Local server setup
https://github.com/blynkkk/blynk-server#blynk-server
Download Blynk local server od blynk.com
Update raspberry pi
curl -sL "https://deb.nodesource.com/setup_6.x" | sudo -E bash -
 sudo apt-get update && sudo apt-get upgrade
 sudo apt-get install build-essential
 sudo npm install -g npm
 sudo npm install -g onoff
 sudo npm install -g blynk-library
Skini blynk library
$ git clone https://github.com/blynkkk/blynk-library.git
$ cd blynk-library/linux
$ make clean all target=raspberry
(https://github.com/blynkkk/blynk-library/tree/master/linux)
instaliraj javu 8
Napravi dvije datoteke za server i mail config u folderu gdje je .jar
cat > server.properties
cat > mail.properties
u rootu pokreni 
java -jar server-0.23.5.jar -dataFolder /home/pi/Blynk -serverConfig /home/pi/server.properties -mailConfig /home/pi/mail.properties
Za automatski start servera odi u /etc/init.d/rc.local i dodaj: 
java -jar /home/pi/server-0.23.5.jar -dataFolder /home/pi/Blynk -serverConfig /home/pi/server.properties -mailConfig /home/pi/mail.properties &
ili
crontab -e
zatim:
@reboot java -jar /home/pi/server-0.23.5.jar -dataFolder /home/pi/Blynk -serverConfig /home/pi/server.properties -mailConfig /home/pi/mail.properties &
u folderu blynk-library/scripts/ uredi file blynk-ser.sh
ip adresu servera, i varijable FROM_TYPE, TO_TYPE u SER i TCP tip
Nakon toga pokreni blynk skriptu 
./blynk-ser.sh -c /dev/ttyS0(ako je samo jedan usb uredaj spojen) -s 192.168.0.104
u blynk-ser.sh scripti promijenis local IP za spajanje hardwarea na server
rezerviraj IP na routerima
u mail.properties postavis svoju mail adresu i u gmailu dopustis stranim (bez certifikata) mailovima slanje primanje

Admin panel :
https://local-IP:9443/admin
