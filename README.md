# Project Arduino

# Garage Opener

Remote open your garage with mobile phone from anywhere

## Getting Started

I am using Arduino with Raspberry as my local server. Idea is to open my garage with app outside from my local network.

### Prerequisites

* Raspberry Pi 3
* Arduino
* Ultrasonic sensor
* Infrared sensor
* Magnetic sensor
* Temprature sensor
* Software for mobile app is Blynk (eseaiset way to do for iOS in my example)
* Backend server configuration runs Blynk config

![Dashboard](https://github.com/mellonZvone/Project-Arduino/blob/master/docs/Screenshot%20(63).png)

### Installing

Local server setup on Raspberry Pi 

Download Blynk local server and more details on this project:

[Blynk github page](https://github.com/blynkkk/blynk-server#blynk-server)


Update raspberry pi

		curl -sL "https://deb.nodesource.com/setup_6.x" | sudo -E bash -
		sudo apt-get update && sudo apt-get upgrade
		sudo apt-get install build-essential
		sudo npm install -g npm
		sudo npm install -g onoff
		sudo npm install -g blynk-library

Download blynk library
		$ git clone https://github.com/blynkkk/blynk-library.git
		$ cd blynk-library/linux
		$ make clean all target=raspberry

	(https://github.com/blynkkk/blynk-library/tree/master/linux)

Install java 8

Create two files for server and mail configuration in folder where your server.jar is located (example /home/pi/):

		cd /home/pi/
		cat > server.properties
		cat > mail.properties

Edit file mail.properties, add your mail

In root start server: 

		java -jar server-0.23.5.jar -dataFolder /home/pi/Blynk -serverConfig /home/pi/server.properties -mailConfig /home/pi/mail.properties

For automatic start this server, go in /etc/init.d/rc.local and add this:

		java -jar /home/pi/server-0.23.5.jar -dataFolder /home/pi/Blynk -serverConfig /home/pi/server.properties -mailConfig /home/pi/mail.properties &

Or

		crontab -e

Edit this file in:

		@reboot java -jar /home/pi/server-0.23.5.jar -dataFolder /home/pi/Blynk -serverConfig /home/pi/server.properties -mailConfig /home/pi/mail.properties &

In folder blynk-library/scripts/ edit file blynk-ser.sh:

	Server ip address(Rpi address), 
	And variable FROM_TYPE, TO_TYPE edit in SER and TCP type

Additional: reserve your server ip in your router dns list

After that start blynk script: 

		./blynk-ser.sh -c /dev/ttyS0(if is connected only one usb device in rpi) -s 192.168.0.104(thats my local server ip)

Admin panel :
		https://local-IP:9443/admin


## Built With

* [Blynk](http://docs.blynk.cc/) - The web framework used