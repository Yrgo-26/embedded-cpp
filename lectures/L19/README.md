# L19 - Arbete med **P02** och tentaförberedelse

## Dagordning
* Arbete med **P02**.
* Genomgång av tentafrågor och riktad repetition.

## Mål med lektionen
* Arbeta vidare med implementationen av **P02** (eller **P02+** om driverdelen är slutförd).
* Repetera centrala begrepp inför sluttentamen.

## Förutsättningar
* God kunskap i C++ (klasser, referenser, RAII, smarta pekare).
* Förståelse för projektets arkitektur och kravspecifikation.

## Litteratur
* Kursboken [Modern Embedded C++](../../info/README.md#litteratur), repetitionsavsnitten - ett per
  kapitel, avsedda just för den här sortens repetition:
    * §1.3 *Review* (modern C++), §2.3 *Review* (klasser), §3.4 *Review* (arv och interfaces),
      §4.3 *Review* (factory), §5.4 *Review* (templates), §6.2 *Review* (flertrådning).
* Bokens bilagor B och C - två kompletta papper med facit, om du vill träna mer än
  [övningstentamen](../../exam/practice_exam.md).

---

## Instruktioner

### Förberedelse
* Läs igenom [uppgiftsbeskrivningen](../../projects/P02/README.md).
* Identifiera vad som återstår att implementera eller förbättra.

### Under lektionen
Arbeta med ert projekt och säkerställ att:
* Arkitekturen är korrekt (interfaces, factory, systemlogik).
* Systemlogiken är tydligt separerad från hårdvaruberoende kod.
* Drivers skapas via factory och ägs via `std::unique_ptr`.

### Tentaförberedelse
* Genomgång av exempeluppgifter och typiska tentafrågor.
* Gå igenom de övningsuppgifter vars testsviter fortfarande rapporterar fel; de pekar på exakt vad
som återstår att förstå. Kör `make test` från repots rot.
* Läs kapitelsammanfattningarna i [kursboken](../../info/README.md#litteratur) för de avsnitt du är
osäker på.

---

## Utvärdering
* Vad är fortfarande oklart inför tentamen?

---

## Nästa lektion
* Tentamen – C++.

---