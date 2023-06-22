# HOME-Deck

uitleg project ....



## Materialen die je nodig hebt:

 - Orange Pi 5 (minimaal 8GB ram) 
 - 7 inch scherm(aangeraden minimaal 1024*600 pixel) 
 - Arduino Micro 
 - 2 joysticks 
 - 16 knoppen 
 - USB-kabels
 - MicroSD-kaart (minimaal 32GB aanbevolen 128GB+) 
 - Behuizing (de 3D bestanden die voor dit project gebruikt kunnen worden kunnen altijd aangepast worden als je hier behoefde aan hebt)

> het kan zijn de de 7inch scherm niet werkt op een Orange pi 5. Dan heb je de volgende materialen nodig om het op te lossen. 
> - usb-c naar HDMI kabbel / adapter
>  - HDMI dummy 

## Stap 1: Verzamel de benodigde materialen
Zorg ervoor dat je alle benodigde materialen hebt verzameld voordat je begint met de bouw van je handheld console. Dit omvat de Orange Pi , het 7 inch scherm, de Arduino Micro, de joysticks, de knoppen en alle vereiste kabels.

## Stap 2: Installeer het Armbian-besturingssysteem
Ga naar website van [Armbian](https://www.armbian.com/orangepi-5/) en download de besturingssysteem met desktop voor je Orange Pi-5.
Volg de instructies op de website van Armbian om het besturingssysteem op een MicroSD-kaart te installeren.
Plaats de MicroSD-kaart in de Orange Pi.
> het is handig om tijdens het instellen van Armbian een groter scherm te gebruiken dan de 7 inch scherm voor dit project. daarnaast heb je een toetsenbord nodig en een muis kan handig zijn. 

## Stap 3: Sluit het 7 inch scherm aan
Verbind het 7 inch scherm met de Orange Pi volgens de instructies van de fabrikant.
Gebruik je een 7inch scherm die via HDMI aangesloten is kan het zijn dat dit niet werkt. 
>de Orange Pi 5 heeft een productie fout waardoor de HDMI poort geen 7 inch schermen ondersteunt. om dit  op te lossen gebruiken we een usb-c naar HDMI kabel / adapter om de 7 inch scherm werkend te krijgen. sluit het scherm aan via de usb-c kabel en reboot de pi (door de stroom er af te halen). als het scherm nog steeds geen beeld geeft probeer dan een ander scherm (een niet 7 inch scherm) aan te sluiten via de HDMI poort van de Orange pi 5. krijg je nu wel beeld (na een reboot) op de 7 inch scherm dan moet er een HDMI dummy in de HDMI poort van de pi gestopt worden om het 7inch scherm werkten te krijgen.

## Stap 4: Installeer Steam als game library
om steam werkten te krijgen te krijgen op een ARM controller (Orange pi) moeten we eerst een paar afhankelijkheden installeren:

    sudo dpkg --add-architecture armhf
    sudo apt update && sudo apt install build-essential git cmake gcc-arm-linux-gnueabihf libc6-dev-armhf-cross libappindicator1 libnm0 libtcmalloc-minimal4 binfmt-support liblttng-ust-dev libcairo2:armhf libgmp10:armhf libvulkan1:armhf libudev-dev:armhf -y


vervolgens een paar programma's nodig voordat we steam kunnen installeren
de applicaties die geïnstalleerd moeten worden zijn:
 - box64 
 
	    git clone https://github.com/ptitSeb/box64
	    cd box64
	    mkdir build; cd build; cmake .. -DRK3588=1 -DCMAKE_BUILD_TYPE=RelWithDebInfo
	    make -j4
	    sudo make install
	    
 - box86

	    cd
	    git clone https://github.com/ptitSeb/box86
	    cd box86
	    mkdir build; cd build; cmake .. -DRK3588=1 -DCMAKE_BUILD_TYPE=RelWithDebInfo
	    make -j4
	    sudo make install

De Orange pi heeft 3D support drivers die ook geïnstalleerd moeten worden.

    sudo add-apt-repository ppa:liujianfeng1994/panfork-mesa
    sudo add-apt-repository ppa:liujianfeng1994/rockchip-multimedia
    sudo apt update
    sudo apt dist-upgrade -y
    sudo apt install mali-g610-firmware rockchip-multimedia-config -y
    sudo reboot

Na het installeren van box64, box86 en de 3D support drivers kunnen we Steam installeren.

    echo 'export STEAMOS=1
    export STEAM_RUNTIME=1
    export DOTNET_SYSTEM_GLOBALIZATION_INVARIANT=1
    export PAN_MESA_DEBUG=gofaster,gl3' | sudo tee /etc/profile.d/steam.sh
    source /etc/profile.d/steam.sh
    cd ~/box86
    ./install_steam.sh

om steam op te starten open je de terminal en run je de command:

    steam

voor meer informatie ga naar > [Installing Steam on the Orange Pi 5 with Armbian](https://jamesachambers.com/installing-steam-on-the-orange-pi-5-with-armbian/)

## Stap 5: Aansluiten controller
Sluit de Arduino Micro aan op de Orange Pi met behulp van een USB-kabel.
Verbind de joysticks en knoppen met de Arduino Micro volgens het electrics schema.

## Stap 6: Programmeer de Arduino Micro
Ga naar website voor Arduino-ontwikkeling en download de Arduino IDE voor je besturingssysteem.
Open de Arduino IDE en maak een nieuw sketch-bestand.
Voeg de code toe die je hebt geschreven om de functies van de joysticks en knoppen te definiëren.
Sluit de Arduino Micro aan op je computer via USB en upload de code naar de Arduino Micro.

## Stap 7: Behuizing en afwerking (optioneel)
Als je een behuizing voor je handheld console wilt gebruiken, volg dan de instructies van de fabrikant om de onderdelen in de behuizing te monteren. Zorg ervoor dat alle componenten stevig zijn bevestigd en dat er voldoende ruimte is voor de kabels en verbindingen.

## Stap 8: Aan de slag met je handheld console
Start de Raspberry Pi op en volg de configuratie-instructies op het scherm om het Armbian-besturingssysteem in te stellen.
Zodra de Raspberry Pi is opgestart, open je de Steam-client en meld je je aan bij je Steam-account.
Je kunt nu beginnen met het installeren en spelen van games op je handheld console!

## Extra bronnen:
Voor meer gedetailleerde informatie over het installeren en instellen van Armbian kun je terecht op [link-naar-armbian-website](https://www.youtube.com/watch?v=dQw4w9WgXcQ).
Informatie over het installeren van Steam op Armbian is te vinden op [link-naar-steam-website].
Raadpleeg de documentatie van Arduino voor meer informatie over het programmeren van de Arduino Micro: [link-naar-arduino-documentatie].

Let op: Zorg ervoor dat je altijd de officiële websites van de genoemde software en documentatie raadpleegt voor de meest recente instructies en informatie.

