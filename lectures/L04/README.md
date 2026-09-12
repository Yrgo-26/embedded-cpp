# L04 - Introduktion till C++

## Dagordning
* Övergång från C till modern C++ i inbyggda system:
  * Headerkonventionerna `.h` kontra `.hpp`.
  * `extern "C"` och `#ifdef __cplusplus` för headerfiler som delas mellan C och C++.
  * Namnrymder.
  * `constexpr` och konstanter vid kompileringstid.
  * `noexcept` och undantagshantering i inbyggda system.
  * Defaultargument.
  * Moderna C++-struktar (medlemsfunktioner, konstruktor/destruktor och inkapsling).
  * Referenser.
  * Nyckelordet `auto`.
  * Funktionstemplates och parameterpack.
  * `[[nodiscard]]`.
* Fortsatt arbete med **P01**.

---

## Mål med lektionen
* Bekanta sig med moderna C++-språkfunktioner som används i inbyggda system.
* Förstå hur C++ kan förbättra struktur och säkerhet i inbyggd mjukvara.
* Känna till varför headerfiler i C++ ges ändelsen `.hpp` i denna kurs, och när `.h` fortfarande är rätt val.
* Förstå hur `extern "C"` gör det möjligt att länka C++-kod mot bibliotek skrivna i C.
* Förstå hur moderna C++-struktar kan gruppera data och beteende i en och samma typ.
* Lära sig hur enkla drivrutiner kan implementeras med hjälp av struktar med medlemsfunktioner, konstruktorer/destruktorer och inkapsling.
* Förstå hur referenser förenklar funktionsanrop jämfört med pekare.
* Kunna använda `[[nodiscard]]` för att förhindra att returvärden ignoreras av misstag.

---

## Förkunskaper
* Kunskap om C-programmering (funktioner, pekare, struktar, etc.).
* Bekantskap med bitmanipulation och begrepp inom inbyggd programmering.

---

## Litteratur
* Kursboken [Modern Embedded C++](../../info/README.md#litteratur), kapitel 1 *Modern Embedded C++ Concepts*:
    * §1.1 *Compiling and Executing Code in Linux*.
    * §1.2 *From C to Modern Embedded C++*.
    * §1.3 *Review* - repetitionsfrågor.
    * §1.4 *Exercises* - lektionens övningar.

---

## Instruktioner

### Förberedelse
* Installera WSL och GCC-kompilatorn enligt beskrivningen i kursboken, §1.1 *Compiling and
Executing Code in Linux*. Där finns också Makefile-mallarna som används genom hela kursen.
* Läs kapitel 1 i kursboken, i första hand §1.2 *From C to Modern Embedded C++*.

### Under lektionen
* Genomför övningarna i kursboken, §1.4 *Exercises*:
  * Ni får tid under lektionen att genomföra övningarna.
  * Lösningarna diskuteras därefter gemensamt i klassen.

### Efter lektionen
* Slutför övningarna i kursboken, §1.4 *Exercises*.
* Skriv dem i [`exercises/`](./exercises/README.md) och kontrollera dem med `make test` från repots rot.
* Lösningsförslag finns [här](./appendix/solutions/README.md).

---

## Utvärdering
* Vad är skillnaden mellan ändelserna `.h` och `.hpp`, och vad avgör vilken som ska användas?
* Vad gör `extern "C"`, och varför behövs `#ifdef __cplusplus` runt det?
* Vad är syftet med `constexpr`?
* Varför används `noexcept` ofta i inbyggda system?
* Hur skiljer sig en C++-strukt från en traditionell C-strukt?
* Varför är konstruktorer och destruktorer användbara i inbyggd C++?
* Vad är syftet med att göra medlemsvariabler privata?
* Vilka fördelar har referenser jämfört med pekare?
* Varför kan templates öka binärstorleken i inbyggda system?
* Vad används parameterpack till?
* Vad gör `[[nodiscard]]`, och på vilka funktioner hör det hemma?

---

## Nästa lektion
* Klasser i C++:
  * Fördjupning i konstruktorer och destruktorer.
  * Nyckelorden `explicit`, `final`, `default` och `delete`.
  * Kopieringskonstruktorer.
  * Flyttkonstruktorer.
  * Tilldelningsoperatorer.
* Fortsatt arbete med **P01**.

---
