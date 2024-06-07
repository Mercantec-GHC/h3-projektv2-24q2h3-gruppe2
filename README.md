### H3-Smart-Kommunikationsplatform - {Gruppe 2}

Her skal alt omkring jeres projekt være. 

Projekt kan findes her: ["Notion link"](https://mercantec.notion.site/Projekt-H3-IoT-og-Serverside-med-Christoffer-og-Kasper-e8980638a8584a72b0c7d718252dbba4?pvs=4)




- Dokumentation
	
 - Man skal bruge:
   *Arduino
   *Arduino Carrier
   *Ledning
   *Pc med Arduino IDE (Hvis ikke uploadet på Arduinoen) og visual studio (Hvis ikke sat op til at man kan åbne siden uden)

    - setup.md
*  Først åbner man Sketchen op i arduino IDE for at uploade programmet til sin arduino som man har sat i computeren
*  Så åbner man Frontend.sln op og kør den for at komme ind på dashboardet

   - bruger_manual.md
* Man sætter sin arduino op med programmet fra "Arduino IDE", Hvorefter at den så vil connecte til et netværk, i den her version Jacobs mobilnetværk.
Så sætter man sin arduino op mod en farve som man gerne vil have scannet og trykker på "00" så går der lidt tid hvor den poster til databasen og så vil den vise på skærmen hvilken farve det er og hvilke rgb værdier du har scannet. Det kan man blive ved med, hvor den vil uploade det til databasen hver gang.

	-- Flowcharts
  
	-- ER diragrammer
  ![image](https://github.com/Mercantec-GHC/h3-projektv2-24q2h3-gruppe2/assets/83217880/a6679aeb-79f7-4285-8479-abefb12a15c1)
	-- Projekt tegning
  ![image](https://github.com/Mercantec-GHC/h3-projektv2-24q2h3-gruppe2/assets/83217880/eb4e9066-3f91-494b-bceb-90a2340b39c2)

	- Kravsspecificationer.md
   [Kravspecifikationer.pdf](https://github.com/user-attachments/files/15609804/Kravspecifikationer.pdf)

	- Case_beskrivelse.md
- Arduino
	-- Biblioteker
	-- Sketches
- Database
  Vi har 2 databaser, 1 som vi selv har lavet og indsat værdier i og 1 som vi fik fra nettet med en masse farver samt RGB værdier til
- Backend (api)
  Så har vi lavet vores API til at kunne post, get, delete og create colors på databasen fra vores arduino
- Frontend
- Tests
.gitignore
README.md

### Projekt pitch:


Vi vil lave en Rgb scanner som scanner de farver man sætter selve arduinoen op imod og så giver rgb værdien og farven tilbage af hvad end man har scannet, og så vil den tage den værdi op på ens dashboard, hvor man kan se de scanninger man har lavet på den bruger og hvilke farver der vil matche til den farve. Vi bruger rgb scanneren og touch sensorerne som er en del af den carrier vi fik med til arduinoen

