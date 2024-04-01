[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1637

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1637/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

TM1637 ist eine Art spezielle LED-Antriebssteuerungsschaltung (Leuchtdiodenanzeige) mit Tastatur-Scan-Schnittstelle und ist intern mit einer digitalen MCU-Schnittstelle, Datenverriegelung, LED-Hochdruckantrieb und Tastatur-Scan integriert. Dieses Produkt verfügt über ein DIP20/SOP20-Gehäuse mit hervorragender Leistung und hoher Qualität, das hauptsächlich für den Displayantrieb von Induktionsherden, Mikrowellenherden und kleinen elektrischen Haushaltsgeräten geeignet ist.

LibDriver TM1637 ist der von LibDriver gestartete Vollfunktionstreiber von TM1637. LibDriver TM1637 bietet digitale Röhrenanzeige, Tastatur-Scanning und andere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver TM1637-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver TM1637 IIC.

/test enthält den Testcode des LibDriver TM1637-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver TM1637-Beispielcode.

/doc enthält das LibDriver TM1637-Offlinedokument.

/Datenblatt enthält TM1637-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_tm1637_basic.h"

uint8_t res;
uint8_t seg;
uint8_t k;
uint8_t number[] = {TM1637_NUMBER_0, TM1637_NUMBER_1, TM1637_NUMBER_2,
                    TM1637_NUMBER_3, TM1637_NUMBER_4, TM1637_NUMBER_5,
                    TM1637_NUMBER_6, TM1637_NUMBER_7, TM1637_NUMBER_8, TM1637_NUMBER_9};

/* init */
res = tm1637_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* write */
res = tm1637_basic_write(0, &number[0], 6);
if (res != 0)
{
    (void)tm1637_basic_deinit();
    
    return 1;
}

...
    
/* read */
res = tm1637_basic_read(&seg, &k);
if (res != 0)
{
    (void)tm1637_basic_deinit();
    
    return 1;
}

/* output */
tm1637_interface_debug_print("tm1637: seg: 0x%02X.\n", seg);
tm1637_interface_debug_print("tm1637: k: 0x%02X.\n", k);

...
    
/* on */
res = tm1637_basic_display_on();
if (res != 0)
{
    (void)tm1637_basic_deinit();
    
    return 1;
}

...
    
/* off */
res = tm1637_basic_display_off();
if (res != 0)
{
    (void)tm1637_basic_deinit();
    
    return 1;
}

...
    
/* deinit */
(void)tm1637_basic_deinit();

return 0;
```
### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/tm1637/index.html](https://www.libdriver.com/docs/tm1637/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.