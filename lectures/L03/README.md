# L03 - Struktar i C (del III)

## Dagordning
* Utökning av GPIO-drivern: Callbacks för interrupts.
* Introduktion till **P01**.

---

## Mål med lektionen
* Kunna implementera callbacks för GPIO-drivern (funktionpekare som anropas vid interrupt).
* Kunna aktivera och inaktivera interrupts för GPIO-enheter.
* Påbörja P01: skapa grundstruktur och påbörja implementation av en timer-driver för ett litet inbyggt system i C.

---

## Förutsättningar
* Genomgång av L01-L02.

---

## Litteratur
* Referensboken [Embedded C](../../info/README.md#litteratur), kapitel 10 *Encapsulation and Polymorphism in C*:
    * §10.1.4 *Function pointers*.
    * §10.1.5 *Worked example: an interrupt-driven `gpio_t` with event flags*.
    * §10.1.2 *Hiding functions with `static`* - frivillig fördjupning: `static` på filnivå och
    funktionspekare som medlemmar i en strukt.
    * §10.2 *Review* - repetitionsfrågor till hela kapitlet.
    * §10.3 *Exercises*, övning 10.3 och 10.5 - frivilliga extraövningar.
* Referensboken [Embedded C](../../info/README.md#litteratur), kapitel 9 *Structs as Drivers*:
    * §9.2 *Review* - repetitionsfrågor till hela kapitlet.
    * §9.3 *Exercises*, övning 9.5 *A pin-reservation table* - samma idé som pinregistret i
    [bilaga A](./appendix/a_exercises.md).
* Inför **P01**: övning 9.6 *A timer driver* och 10.4 *An opaque timer* bygger en timer-driver med
callback, som i 10.4 görs opaque. Bokens funktionsnamn skiljer sig från projektets; det är
[kravspecifikationen för P01](../../projects/P01/README.md) som gäller.

Bokens driver i §10.1.5 anropar inte callbacken från avbrottsrutinen: ISR:en sätter bara en flagga,
och callbacken anropas sedan från `main()`-loopen. Lektionens driver anropar callbacken direkt från
ISR:en. Jämför de två och fundera på för- och nackdelar.

---

## Instruktioner

### Förberedelse
* Repetera innehållet i [L01](../L01/README.md).
* Repetera innehållet i [L02](../L02/README.md).
* Läs §10.1.4 - §10.1.5 i Embedded C.
* Läs igenom uppgiftsbeskrivningen för **P01** [här](../../projects/P01/README.md).

### Under lektionen
* Genomför övningsuppgifterna i [bilaga A](./appendix/a_exercises.md):
    * Ni får tid under lektionen att genomföra övningarna.
    * Lösningarna diskuteras därefter gemensamt i klassen.

### Efter lektionen
* Genomför gärna övning 9.5, 10.3 och 10.5 i Embedded C. Kodövningarna har inget tryckt
lösningsförslag, men frågan övning 9.5 ställer besvaras i bokens appendix B *Answers to the
Exercises*.
* Läs §9.2 och §10.2 *Review* inför övergången till C++ i [L04](../L04/README.md).

---

## Lektionsanteckningar
* Lektionsanteckningar finns [här](./notes/README.md).

---

## Utvärdering
* Vad är en callback och varför används den i GPIO-drivern?
* Hur anropas en callback i er implementation?

---

## Nästa lektion
* Övergång från C till modern C++ i inbyggda system.
* Fortsatt arbete med **P01**.

---
