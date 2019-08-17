# Meat Starto

PORT SDL1.2 PS3 - POC 

Para hacer funcionar el port lo primero es configurar el enterno de trabajo de ps3. 

https://github.com/ps3dev/PSL1GHT
https://github.com/ps3dev/ps3libraries
https://github.com/ps3dev/ps3toolchain

Ademas usaremos ps3load para ejecutar codigo de forma remota con "make run"
Para poder hacer logs usaremos netcat: "socat udp-recv:18194 stdout"

Con esto ya estariamos preparados para ejecutar codigo sobre la ps3.

En nuestro caso necesitamos compilar nuestro juego y las dependencias, es por eso que tendremos que compilar box2d 
para power pc, esto lo haremos usando la magia de CMAKE, subo el fichero toolchain-psl1ght.cmake para poder generar un 
make que use el compilador de ppc.


