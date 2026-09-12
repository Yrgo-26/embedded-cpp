# L06 - Klasser (del II)

## Dagordning
* Vidare arbete med klasser.
* Fortsatt arbete med **P01**.

---

## Mål med lektionen
* Öva på implementation av klasser, specifikt för inbyggda system.

---

## Förutsättningar
* Grundläggande kännedom om C++ (klasser, konstruktorer, const).

---

## Litteratur
* Kursboken [Modern Embedded C++](../../info/README.md#litteratur), kapitel 2 *Classes*:
    * §2.4 *Exercises*, övningsset 4 *Timer Class* - lektionens huvudövning.
    * §2.3 *Review* - repetitionsfrågor till hela kapitlet.
* [Bilaga A](./appendix/a_repetition.md): Repetitionsuppgift.
* [Bilaga B](./appendix/b_exercises.md): Ytterligare övningsuppgifter - riktig GPIO-driver för
ATmega328P. Denna finns inte i boken.

---

## Instruktioner

### Förberedelse
* Repetera innehållet i [L05](../L05/README.md).
* Om ni har tid, genomför repetitionsuppgiften i [bilaga A](./appendix/a_repetition.md).

### Under lektionen
* Genomför övningsuppgifterna i [bilaga B](./appendix/b_exercises.md):
    * Ni får tid under lektionen att genomföra övningarna.
    * Lösningarna diskuteras därefter gemensamt i klassen.
* Ytterligare övningsuppgifter finns i [Bilaga B](./appendix/b_exercises.md).
### Efter lektionen
* Slutför övningsset 4 *Timer Class* i kursboken, §2.4 *Exercises*.
* Skriv dem i [`exercises/`](./exercises/README.md) och kontrollera dem med `make test` från repots
  rot.
* Lösningsförslag finns [här](./appendix/solutions/README.md).

---

## Utvärdering
* Varför passar en klass bra för att representera en GPIO eller timer?
* Vad är syftet med destruktorn i denna klass?
* Sök på RAII (`Resource Acquisition Is Initialization`) - Vad innebär det i praktiken i den här uppgiften?

---

## Nästa lektion
* Interfaces (abstrakta klasser) för att definiera en gemensam uppsättning metoder.
* Arv som ett verktyg för att implementera interfaces.
* Fortsatt arbete med **P01**.

---
