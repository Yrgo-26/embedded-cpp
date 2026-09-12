# L14 - Factory-mönster med smarta pekare, arbete med **P02**

## Dagordning
* Problem med manuell minneshantering.
* Introduktion till smarta pekare (`std::unique_ptr`).
* Factory som returnerar `std::unique_ptr`.
* Fortsatt arbete med **P02**.

---

## Mål med lektionen
* Förstå varför smarta pekare används i stället för råa pekare.
* Förstå principen bakom `std::unique_ptr`.
* Kunna implementera en factory som returnerar `std::unique_ptr`.
* Kunna låta systemlogiken äga drivers via `std::unique_ptr`.

---

## Förutsättningar
* Genomgång av L13 (factory med råa pekare).
* Grundläggande kunskap om klasser och interfaces i C++ (L05–L08).

---

## Litteratur
* Kursboken [Modern Embedded C++](../../info/README.md#litteratur), kapitel 4 *The Factory Pattern*:
    * §4.2 *Driver Factory with Smart Pointers (Abstract Factory)*.
    * §4.4 *Exercises*, övningsset 4 - lektionens övning.
    * §4.3 *Review* - repetitionsfrågor till hela kapitlet.

---

## Instruktioner

### Förberedelse
* Repetera L13.
* Läs igenom kursboken, §4.2 *Driver Factory with Smart Pointers (Abstract Factory)*, för information om factories 
med smarta pekare.
* Läs igenom factory-delen i [P02](../../projects/P02/README.md).

---

### Innan lektionen
* Genomför följande [repetitionsuppgift](./appendix/a_repetition.md).

### Under lektionen
* Följ genomgången av smarta pekare och factory-mönstret.
* Fortsätt arbeta på **P02** efter genomgången.

### Efter lektionen
* Slutför övningarna i kursboken, §4.4 *Exercises*, övningsset 4,.
* Skriv dem i [`exercises/`](./exercises/README.md) och kontrollera dem med `make test` från repots
  rot.
* Lösningsförslag finns [här](./appendix/solutions/README.md).

---

## Lektionsanteckningar
Ett exempelprogram där en factory med smarta pekare används för att skapa instanser i systemlogik finns här: [main.cpp](./notes/source/main.cpp).

## Utvärdering
* Vad är skillnaden mellan råa pekare och `std::unique_ptr`?
* Vad händer när en `unique_ptr` går ur scope?
* Varför är `unique_ptr` lämplig i factory-mönstret?
* Vad händer om man försöker kopiera en `unique_ptr`?

---

## Nästa lektion
* Templates, type traits och constraints.
* Fortsatt arbete med **P02**.

---
