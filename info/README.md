# Kursinfo

## Lärare
Erik Pihl ([erik.axel.pihl@gmail.com](mailto:erik.axel.pihl@gmail.com))

---

## Förkunskaper
Kursens ämne är **drivrutinsdesign och övergången från C till modern C++**, inte C-språkets eller
mikrokontrollerns grunder. Kursen förutsätter att du har följande på plats:

* C-programmering: datatyper, funktioner, struktar och enumerationer, pekare, funktionspekare,
  dynamiskt minne och makron.
* Bitoperationer och registernära I/O på ATmega328P: `DDRx`, `PORTx` och `PINx`.
* Att bygga och flasha ett program till Arduino Uno.
* Avbrott: externa avbrott och pin change interrupts.
* Timers: prescaler, Normal Mode och CTC Mode, och icke-blockerande tidsstyrning.
* Seriell kommunikation via UART.

Behöver något av det fräschas upp står allt i
[Embedded C](https://github.com/qrtech-academy/embedded-c/blob/main/book/embedded-c.pdf), en fritt
tillgänglig bok på engelska som går från C-språket till avbrottsdrivna drivrutiner på ATmega328P:
C-grunderna i kapitel 1, register, bitoperationer och flashning i kapitel 2, avbrott i kapitel 3,
timers i kapitel 5 och UART i kapitel 6. Kapitel 4, 7 och 8 - ADC, EEPROM och watchdog - förutsätts
inte, men samma typer av kringkretsar återkommer som drivrutiner i **P02**. Bokens två
övningsskrivningar i bilaga D och E, med lösningsförslag i bilaga F och G, är ett snabbt sätt att
pröva om förkunskaperna sitter, och bilaga A visar hur bokens exempel körs i en simulator om du
inte har något kort till hands.

Ingenting av det lärs ut från grunden. Det kursen lär ut är hur drivrutiner struktureras: först i C,
med struktar, opaque structs och callbacks i [L01](../lectures/L01/README.md) -
[L03](../lectures/L03/README.md), där bokens kapitel 9 och 10 är [litteratur](#litteratur), och
sedan i modern C++.

---

## Kursplan – Hårdvarunära programmering C/C++

| Föreläsning | Ämne |
|-------------|------|
| L01 | Struktar i C (del I) |
| L02 | Struktar i C (del II) |
| L03 | Struktar i C (del III) |
| L04 | Introduktion till C++ |
| L05 | Klasser (del I) |
| L06 | Klasser (del II) |
| L07 | Arv och interfaces (del I) |
| L08 | Arv och interfaces (del II) |
| L09 | Arv och interfaces (del III) |
| L10 | Arv och interfaces (del IV) |
| L11 | Konfiguration av ESP32 och utvecklingsmiljö |
| L12 | Arbete med **P02** |
| L13 | Factory-mönster, arbete med **P02** |
| L14 | Factory-mönster med smarta pekare, arbete med **P02** |
| L15 | Templates, type traits och constraints, arbete med **P02** |
| L16 | Klasstemplates, arbete med **P02** |
| L17 | Flertrådning och synkroniseringsmekanismer, arbete med **P02** |
| L18 | Övningstentamen, arbete med **P02** |
| L19 | Arbete med **P02** och tentaförberedelse |
| L20 | Tentamen – C++ |

---

## Examination och betygsnivåer

### Upplägg
* Två projekt (**P01** - **P02**).
* En skriftlig tentamen.

### Poängfördelning
* **P01** ger upp till 2 poäng (**G** = 1p, **VG** = 2p).
* **P02** ger upp till 4 poäng (**G** = 2p, **VG** = 4p).
* Den skriftliga tentamen ger upp till 4 poäng (**G** = 2p, **VG** = 4p).

### Betygsnivåer
Totalt 10 poäng:
* 5 <= **G** < 7 poäng
* 7 <= **VG** <= 10 poäng

För godkänt ska samtliga examinerande moment vara godkända.

---

## Kursmaterial

### Litteratur
Kursens huvudbok, som lektionernas READMEs kallar *kursboken*, är **Modern Embedded C++**. Den är
kursens enda text för C++-delen. **Embedded C** och **DevOps** är referenslitteratur, som används
för enskilda moment: förkunskaperna och C-delen respektive Git, repo-organisation och kodformatering
i **P02**. Alla tre är PDF:er på engelska, och varje lektions README anger vilka kapitel och avsnitt
som hör till lektionen.

#### Kursboken: Modern Embedded C++
Kursboken är **[Modern Embedded C++](https://github.com/qrtech-academy/modern-embedded-cpp/blob/main/book/modern-embedded-cpp.pdf)**
(PDF, engelska). Den täcker kursens C++-del i sex kapitel, och varje lektions README anger vilket
kapitel som hör till lektionen:

| Kapitel | Ämne | Lektioner |
|---------|------|-----------|
| 1 | Modern embedded C++: `.hpp`, `extern "C"`, namnrymder, `constexpr`, `noexcept`, struktar, referenser, `auto`, funktionstemplates, `[[nodiscard]]` | **L04** |
| 2 | Klasser: konstruktorer, destruktorer, kopiering och flytt, `explicit`, `final`, `default`, `delete` | **L05** - **L06** |
| 3 | Arv och interfaces: virtuella metoder, abstrakta klasser, polymorfism | **L07** - **L10** |
| 4 | Factory-mönstret: råa pekare, smarta pekare, dependency injection | **L13** - **L14** |
| 5 | Templates: funktionstemplates, klasstemplates, type traits, kodstorlek | **L15** - **L16** |
| 6 | Flertrådning: trådar, mutex, atomics, `condition_variable`, `future`, prioritetsinversion | **L17** |

Tabellen är översikten. Varje lektions README anger i sin tur **vilka avsnitt** i kapitlet som hör
till just den lektionen, vilket spelar roll där kursen delar ett kapitel över flera lektioner -
kapitel 2 över L05 och L06, kapitel 3 över L07 till L10, kapitel 4 över L13 och L14, och kapitel 5
över L15 och L16. Bokens repetitionsavsnitt och dess två självrättande tentamenspapper används i
[L18](../lectures/L18/README.md) och [L19](../lectures/L19/README.md).

Boken bor i sitt eget repo,
[qrtech-academy/modern-embedded-cpp](https://github.com/qrtech-academy/modern-embedded-cpp), och länken ovan pekar på filen i `main` - alltså alltid
den senaste utgåvan. Den kopieras därför inte in i detta repo. I samma repo finns även bokens
källkod, samt kursens övningar och lösningsförslag på engelska, om du vill jämföra.

Boken är kursens enda text för C++-delen. Teorin och övningarna dubbleras alltså inte på svenska -
lektionernas READMEs anger vilka avsnitt som hör till lektionen, och du läser dem i boken.

#### Referenslitteratur
Referensböckerna läses i utdrag, inte från pärm till pärm; tabellerna nedan visar vilka kapitel
som används och var.

##### Embedded C: förkunskaper och C-delen
Till C-delen (**L01** - **L03**) används de två sista kapitlen i
**[Embedded C](https://github.com/qrtech-academy/embedded-c/blob/main/book/embedded-c.pdf)**:

| Kapitel | Ämne | Lektioner |
|---------|------|-----------|
| 9 | Struktar som drivrutiner: `self`-konventionen, uppdelning i header- och källkodsfil | **L01**, **L03** |
| 10 | Inkapsling och polymorfism i C: `static`, opaque structs, funktionspekare, callbacks, vtables | **L02** - **L03** |

Bokens drivrutiner följer samma mönster som lektionernas, men byggs upp i en annan ordning och med
delvis andra namn - bokens opaque `gpio_t` skapas till exempel med `gpio_create()`, lektionens med
`gpio_new()`. Koden i lektionsanteckningarna, och kravspecifikationen för **P01**, är det som
gäller i kursen. Bokens tidigare kapitel täcker kursens
[förkunskaper](#förkunskaper). §10.1.6, om vtables, motsvarar
[C-exemplet i L07](../lectures/L07/examples/c_interface/README.md).

Boken bor i sitt eget repo, [qrtech-academy/embedded-c](https://github.com/qrtech-academy/embedded-c), och länken ovan pekar på filen i
`main` - alltså alltid den senaste utgåvan.

##### DevOps: Git, repo-organisation och kodformatering
När grupprojektet **P02** startar, i **L11** och **L12**, används de tre första kapitlen i
**[DevOps](https://github.com/qrtech-academy/devops/blob/main/book/devops.pdf)**:

| Kapitel | Ämne | Lektioner |
|---------|------|-----------|
| 1 | Git och samarbete: commit-grafen, brancher och pull requests, bra commits, code review | **L11** - **L12** |
| 2 | Repo-organisation: standardlayouten, en ingång för bygget, `.gitignore` | **L11** |
| 3 | Kodformatering: `clang-format`, `.clang-format` och formatkontroll i CI | **L12** |

Repo-organisation möter du redan från första lektionen: det här repot följer i stort
standardlayouten i kapitel 2, med `make build`, `make test` och `make format` som ingångar, och dess
`.clang-format` är samma stilfil som kapitel 3 skriver ut. Den filen ska även användas i **P02**.
Git-kommandona som gås igenom under L11 och L12 finns dessutom som lektionsanteckningar på svenska.

Boken bor i sitt eget repo, [qrtech-academy/devops](https://github.com/qrtech-academy/devops), och länken ovan pekar på filen i
`main`, alltså alltid den senaste utgåvan.

#### Bilagor
Utöver böckerna finns **bilagor** för det böckerna inte täcker:
* **C-delens** struktintroduktion, övningsuppgifter och repetitionsuppgift (**L01** - **L03**).
* ESP32-konfigurationen (**L11**).
* **Repetitionsuppgifter** inför **L14**, **L15** och **L17**.
* **Övningar med AVR-hårdvara**: GPIO-drivern i **L06** och GPIO-interfacet i **L08**, samt det
  trådsäkra interfacet i **L10**.
* **Video tutorials** som länkas i samband med de lektioner de behandlar.

### Hårdvara
Följande hårdvara, som finns på skolan, kommer att användas under kursen:
* **Arduino Uno**: 
    * För **P01** - **P02** samt implementering av drivers under den första delen av kursen.
    * Använd era kort från tidigare kurser.
* **ESP32-S3**: 
    * För **P02** samt senare kurser. 
    * Finns tillgängliga på skolan.

### Mjukvara
* [Visual Studio Code](https://code.visualstudio.com/download):
    * Primär editor i denna och framtida kurser.
* [Microchip Studio](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio#Downloads):
    * För kompilering och flashning av **Arduino Uno**.
    * Används enbart för kompilering och flashning, i övrigt används Visual Studio Code.
* kursboken, §1.1 *Compiling and Executing Code in Linux*:
    * För mellanstora kodexempel i terminalmiljö.
* [ESP‑IDF](../lectures/L11/appendix/a_installation.md):
    * För kompilering och flashning av **ESP32-S3**.
* [Online C compiler](https://www.onlinegdb.com/online_c_compiler):
    * För kompilering och körning av mindre program i terminalmiljö.
    * För att kompilera och köra C++-kod, byt språk till **C++17** i det övre högra hörnet.

---

## Övningsuppgifter och testsvit
Varje C++-lektion avslutas med övningsuppgifter, och till varje uppgiftssamling finns en **färdig
testsvit** som kontrollerar din lösning. Du skriver aldrig några tester själv i denna kurs - det
kommer i kursen **hårdvarunära testning**, och ordningen är avsiktlig: här får du först se vad en
testsvit är bra för.

Klona repot tillsammans med testramverket, som är en submodul:

```bash
git clone --recursive <repo-url>
```

(I en klon som gjorts utan `--recursive`, kör `git submodule update --init` en gång.) Skriv dina
lösningar i `lectures/LNN/exercises` - varje lektions README anger vilken fil som ska ligga var -
och kör från repots rot:

```bash
make test               # Samtliga lektioners tester, mot din kod.
make test SOLUTIONS=1   # Samma tester, mot lösningsförslagen.
```

En uppgiftssamling du inte har börjat på rapporteras som `SKIP`, tillsammans med den fil testerna
väntar på; så snart filen finns körs dess tester. Där en övning anger exempelutdata jämför testerna
ditt programs utskrift med den, tecken för tecken.

Följande behövs för att kunna köra testerna, och ingår i `build-essential` enligt
kursboken, §1.1 *Compiling and Executing Code in Linux*:
* `g++` och `make`.
* `git`, för submodulen.

---
