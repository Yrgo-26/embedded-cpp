# L17 - Flertrådning och synkroniseringsmekanismer, arbete med **P02**

## Dagordning
* Introduktion till flertrådning i C++ (`std::thread`).
* Concurrency kontra verklig parallellism - en kärna kontra flera kärnor.
* Schemaläggning: tidsdelning kontra samarbetande.
* Data races och varför de är farliga.
* Kritiska sektioner med `std::mutex` och `std::lock_guard`.
* Skillnaden mellan `std::mutex` och `std::atomic`.
* Signalering mellan trådar med `std::condition_variable`.
* Bakgrundsuppgifter med `std::future` och `std::async`.
* Prioritetsinversion - en vanlig fallgrop i inbyggda system.
* Fortsatt arbete med **P02**.

---

## Mål med lektionen
* Förklara vad en tråd är och hur den skapas med `std::thread`.
* Förklara skillnaden mellan concurrency och parallellism.
* Förklara preemptiv och samarbetande schemaläggning.
* Förklara vad en data race är och varför det leder till *undefined behavior*.
* Använda `std::mutex` och `std::lock_guard` korrekt.
* Förklara när `std::atomic` räcker och när `std::mutex` krävs.
* Använda `std::condition_variable` för att signalera mellan trådar utan aktiv väntan.
* Starta asynkrona uppgifter med `std::async` och hämta resultat via `std::future`.
* Förklara vad prioritetsinversion är och varför `std::mutex` inte löser det på ett RTOS.

---

## Förutsättningar
* God kunskap i C++ (klasser, referenser, RAII).
* Grundläggande förståelse för programflöde och livscykel.

---

## Litteratur
* Kursboken [Modern Embedded C++](../../info/README.md#litteratur), kapitel 6 *Multithreading and Synchronization*:
    * §6.1 *Multithreading and Synchronization in C++*.
    * §6.3 *Exercises* - lektionens sju övningsset.
    * §6.2 *Review* - repetitionsfrågor till hela kapitlet.

---

## Instruktioner

### Förberedelse
* Läs kapitel 6 i kursboken, §6.1 *Multithreading and Synchronization in C++*.

### Innan lektionen
* Genomför repetitionsuppgiften i [bilaga A](./appendix/a_repetition.md).

### Under lektionen
* Fundera på om flertrådning kan vara lämpligt i **P02**:
    * Identifiera delar i **P02** där delad data förekommer.
    * Fundera på hur dessa skulle skyddas i en flertrådad miljö.
* För ytterligare information, se följande [video tutorial](https://www.youtube.com/watch?v=jaI_mufDQ2I), som behandlar mutex i C och C++. 

### Efter lektionen
* Slutför övningarna i kursboken, §6.3 *Exercises*.
* Skriv dem i [`exercises/`](./exercises/README.md) och kontrollera dem med `make test` från repots
  rot.
* Lösningsförslag finns [här](./appendix/solutions/README.md).

---

## Utvärdering
* Vad är skillnaden mellan `mutex` och `atomic`?
* Vad är ett data race?
* Vad är skillnaden mellan concurrency och parallellism?
* När skulle du använda en `condition_variable` i stället för att polla i en loop?
* Vad är prioritetsinversion, och varför ska man vara försiktig med `std::mutex` på ett RTOS?

---

## Nästa lektion
* Genomförande av övningstentamen.
* Fortsatt arbete med **P02**.

---
