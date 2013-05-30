default:client server
	make clean
client:client.o
	gcc -o client client.o -lpthread
client.o:client.c chat.h
	gcc -c client.c -lpthread
server:server.o userinfo.o
	gcc -o server server.o userinfo.o -lpthread
server.o:server.c chat.h server.h
	gcc -c server.c -lpthread	
userinfo.o:userinfo.c user.h
	gcc -c userinfo.c
clean:
	rm *.o
