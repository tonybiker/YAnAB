///////////////////////////////////////////////////////////////////////////
// Codice YAnAB                                                        //
// Yet Another Airsoft bomb                                                     //
// Modalita' : Disinnesco (combinazione) Domination (Mantieni il presidio) //
// Accessori: Sensore di prossimitÃ , sensore di scuotimento, antitamper  //
// STL e BOM su Thingverse: link al progetto                             //
// Progetto di Antonio Scalia                                            //
///////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//////////////////////////////////////////////////////////// Avvio tastiera
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
/////////////////////////////////////////////////////////////Tastiera pronta

 ////////////////////////////////
 // Inizializzazione variabili //
 ////////////////////////////////
int PinBatt = 0;   // pin controllo batteria (partitore di tensione)
float Vmax = 12.6; //Valore massimo tensione batteria Lipo 3s
float Vmin = 9.6;  //Valore minimo tensione batteria Lipo 3s
float R1 = 100000; //Valori resistenze partitore di tensione per monitoraggio batteria
float R2 = 10000;
float tensione = 0;
String passwd="";

void setup() {
  ////////////////////////////////
  // Bootstrap
  ////////////////////////////
  Serial.begin(9600);              // initialize serial 
  lcd.begin();                      // initialize the lcd 
  pinMode (PinBatt, INPUT);        // initialize pin controllo batteria
  
 lcd.clear(); 
 lcd.print("Welcome to ASBmb");
  
  //////////////////////////////
  // Controllo voltaggio batteria
  //////////////////////////////
  lcd.setCursor(0, 1);
  
  tensione = batteryvoltage();
  if (tensione > Vmin) {
    lcd.print("Tensione batteria:");
    lcd.print(tensione);
  }                
  else {
    lcd.print("Batteria scarica");
    lcd.print(tensione);
  }
 
char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }


  // Controllo sirena
  // Interrupt antitamper
  // Interrupt scuotimento
  // Interrupt Ultrasonic
  // Interrupt Domination
  // Welcome message
}

void loop() {
  // Main menu: 1-Setup 2-Innesco 3-Domination
  // Setup: 1-Time 2-Sensori 3-Password #-Back
  // Innesco: 1-Start #-Back
  // Domination: 1-Start 2-Last Result #-Back
char key = keypad.getKey();
  if (key != NO_KEY)
  {
    Pulisci3e4Riga();
    if (key=='#') // Tasto di reset
      PulisciRigaPassword();
    else if (key=='*') // Tasto di invio
    {
      if (passwd.length()!=0)
      {
          lcd.setCursor(0, 2); // 1° colonna - 3° riga
          if (passwd=="123456")
             lcd.print("||   BENVENUTO    ||"); 
          else
             lcd.print("** ACCESSO NEGATO **"); 
          PulisciRigaPassword();
      }
      else
         MessaggioErrore("Nessun carattere!");
    }
    else
    {
        if (passwd.length()<10)
        {
           lcd.setCursor(pos++, 1);
           lcd.print("*"); // Maschero il numero digitato
           passwd=passwd+String(key);
        }
        else
        {
           MessaggioErrore("Troppi caratteri!");
           PulisciRigaPassword();
        }
    }
  }
}



