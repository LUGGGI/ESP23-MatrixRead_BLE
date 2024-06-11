# GoWannaGo

## How to use

- Download VSCode https://code.visualstudio.com/Download
- Clone repository (must be local drive, no network drive), can youse Open in your IDE...
- Open repository in VSCode, if you cloned with VSCode option should pop up in down right corner
- Install recommended extensions, look for another popup to install those or use the extension menu
- Compile / Upload code with buttons in bottom bar, with the house symbol you can control platformIO

### Upload on multible Controllers

* To upload run upload.bat in _upload, it will upload the file in .pio
  * in .bat file change COM to port where controller is connected
  * to upload other versions change path

### Anleitung für SupperTuxKart

Schnelle grünes Blinken bedeutet --> lange inaktiv --> System geht aus wenn nicht betätigt wird

#### Einschalten

1. Matte/Band muss zum Controller verbunden sein (Matte: rot ist rechts)
2. Beide müssen in Ruhe/Unbelastet sein
3. Einschalten. Beim ersten Mal BT-Geräte mit Windows verbinden
4. Spiel starten "Einzelspieler" --> "Wilber" (färht langsam) --> Zeitrennen --> Strecke (links unten): Nessis Teich

#### Funktionen

Band für bremsen/rückwärts
Matte für Steuerung
Vollgas durch drücken/springen auf linkes Feld in der Matte. 
Nitro-Boost springen auf beide Felder
Adler-Rettung druch drücken/springen auf rechtes Feld in der Matte

                        ->    SuperTux                        https://gamepad-tester.com/
jump beide    ->    Nitro        Gampepad-Taste2        => B1                                            (nitro 1s lang, extra beschleunigen)
jump left     ->    Bremse    Achse 3-                    => Axis 3 toggle 1\<->0            (beschleunigen)
jump right     ->    Retten    Gampepad-Taste5        => B4                                            (Adler = zurück auf die Bahn)

Verlagerung links/rechts => Axis 0 (-0,6..0,6)

**Controllerconfig**:
"SuperTuxKartPortable\\Data\\supertuxkart\\config-0.10\\input.xml"

