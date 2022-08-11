//Incluimos la libreria BLUETOOH
#include "BluetoothSerial.h"
//Verificacion de la habilitacion correcta del Bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Variable de tipo de entero para el cambio de estado del led interno
int cambio = 0;
//Inicializamos y podemos usar la libreria en nuestro codigo. 
BluetoothSerial SerialBT;

//void es para declarar funciones.
//setup se usa para iniciar, configurar y se ejecutara una sola vez por cada encendido y apagado. 
void setup() {
  
//Establecer la velocidad de datos de bits por segundo (baudios) en la transmision de datos en serie. 
//Asegurarse que esta debe ser igual a la del monitor serial.
  Serial.begin(115200); 
//Nombre del dispositivo Bluetooth.
  SerialBT.begin("ESP32_DISPOSITIVO1");
//Imprime en el Monitor Serial.
  Serial.println("EL DISPOSITIVO ESTA LISTO Y PUEDES CONECTARTE MEDIANTE BLUETOOTH!");
//Configura el pin 4 como salida.
  pinMode(4,OUTPUT);
//Manda un valor alto al pin 4 y el rele no se activa.
  digitalWrite(4,HIGH);
}

//void es para declarar funciones.
//loop ejecutara repetitivamente.
void loop() {
  
//while ejecutara repetitivamente hasta que deje de cumplirse la condicion cambio == 0.
  while(cambio == 0){
//Condicional if si se cumple o no.
//Serial.available datos disponibles para la lectura en el puerto serie Bluetooth.
//Si encuentra datos disponibles para la lectura en el puerto serie Bluetooth se cumple la condicional if.
    if(SerialBT.available()){
//SerialBT.read()=='a' lee los datos del puerto serie y si en cuentra el caracter "a". 
//Si encuentra el caracter "a" se cumple la condicional if y pasa a la sigueinte linea.
    if (SerialBT.read()=='a'){
//Manda un valor bajo al pin 4 y el rele se activa.
    digitalWrite(4,LOW);
//Imprime en el Monitor Serial.
    Serial.println("ENCENDIDO");
//ahora la variable cambio tiene un valor de 1 y se rompe el bucle while.  
    cambio = 1;
    }
//De lo contratrio si no se encuentra el caracter "a" la variable cambio tiene un valor de 0.
    else{
      cambio = 0;
    }
    }
  }
  
//Condicional if si se cumple o no.
//Serial.available datos disponibles para la lectura en el puerto serie Bluetooth.
//Si encuentra datos disponibles para la lectura en el puerto serie Bluetooth se cumple la condicional if.  
  if(SerialBT.available()){
//SerialBT.read()=='b' lee los datos del puerto serie y si en cuentra el caracter "b". 
//Si encuentra el caracter "b" se cumple la condicional if y pasa a la sigueinte linea.
  if (SerialBT.read()=='b'){
//Manda un valor alto al pin 4 y se desactiva el rele.
    digitalWrite(4,HIGH);
//Imprime en el Monitor Serial.
    Serial.println("APAGADO");
//La variable cambio tiene un valor de 0 y volver al bucle while con la condicional while(cambio == 0).
    cambio = 0;
    
  }
  }

}
