# Project sources
srvsrc:=$(shell ls Mproject/server/*.java)
clisrc:=$(shell ls Mproject/client/*.java)
msgsrc:=$(shell ls Mproject/message/*.java)
guisrc:=$(shell ls Mproject/gui/*.java)
dispsrc:=$(shell ls Mproject/manager/*.java)

# directory and structure
libdir=Mproject/lib
classpath=.:$(libdir)

# specific libs
libsql=$(libdir)/mssql-jdbc-6.4.0.jre8.jar

# add more libs to end of line if needed
libs=$(libsql)

all: message server client gui mproject displaymgr

mproject: Mproject/Mproject.java
	javac -cp $(classpath) -g Mproject/Mproject.java

server: $(srvsrc)
	javac -cp $(classpath) -g Mproject/server/Server.java

client: $(clisrc)
	javac -cp $(classpath) -g Mproject/client/Client.java

message: $(msgsrc)
	javac -cp $(classpath) -g $(msgsrc)

gui: $(guisrc)
	javac -cp $(classpath) -g $(guisrc)

displaymgr: $(dispsrc)
	javac -cp $(classpath) -g $(dispsrc)

runserver: Mproject/server/Server.class
	java Mproject/server/Server

runclient: Mproject/client/Client.class
	java Mproject/client/Client

jar: all
	jar cfm Mproject.jar manifest.txt Mproject/Mproject.class Mproject/client/*class Mproject/manager/*class Mproject/gui/*class Mproject/util/*class Mproject/message/*class Mproject/lib/mssql-jdbc-6.4.0.jre8.jar
	

clean:
	rm -f **/*.class 
	rm -f **/**/*.class 

run: all
	java -cp $(libsql):. Mproject/Mproject

.PHONY: clean
