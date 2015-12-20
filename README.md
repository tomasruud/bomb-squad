# Dokumentasjon
Videodemonstrasjon av løsningen kan sees her: https://youtu.be/AQeiSyJKehU

## Mappestsruktur
- Filnavn og struktur

## Forutsetninger
Det er en del forutsetninger som ligger til grunn for at løsningen skal kunne kjøres. For det første må alle filene i mappen `res` legges over på roten av et minnekort som støttes av Arduino's SD-bibliotek, og settes i skjermen, slik at grafikk kan bli lastet inn i programmet.

- Kalibrere akselerometeret
- Krever ArduinoThread-biblioteket - https://github.com/ivanseidel/ArduinoThread

## Kode
![Programflyt](./docs/flow.svg)
- Minnefragmentering ifht new og delete
- PROGMEM
- Animasjon
- Overganger
- Scener
- Levler

## Fritzing
Koblingsskjemaet for løsningen ligger i mappen `docs`, i Fritzing-formatet `.fzz` og som vektorgrafikk `.svg`. Jeg har forsøkt å gjøre skjemaet så oversiktlig som mulig, men i og med at alle portene er i bruk, blir det naturlig nok en del kaos.

![Fritzing skjema](./docs/schematic.svg)

## Kilder
### "Tråder"
- https://github.com/ivanseidel/ArduinoThread

### Minneproblematikk
- https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory
- http://www.avrfreaks.net/forum/tut-c-gcc-and-progmem-attribute?name=PNphpBB2&file=viewtopic&t=38003
- https://www.arduino.cc/en/Reference/PROGMEM
- http://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html

### Grafikk
- Eksplosjonsbilde - http://images.alphacoders.com/305/30521.jpg
- Borat - http://41.media.tumblr.com/677f0fe299bc53879495d2612ea34e73/tumblr_mki0j9fxK81s5jjtzo1_500.png
