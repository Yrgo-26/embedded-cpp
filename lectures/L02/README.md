# L02 - Struktar i C (del II)

## Dagordning
* Slutförande av GPIO-drivern i dess nuvarande skick.
* Inkapsling med opaque struct (fördeklaration i header, implementation i motsvarande källkodsfil).

---

## Mål med lektionen
* Kunna använda opaque structs för att dölja implementationsdetaljer i en drivrutin.

---

## Förutsättningar
* Genomgång av L01.

---

## Litteratur
* Boken [Embedded C](../../info/README.md#litteratur), kapitel 10 *Encapsulation and Polymorphism in C*:
    * §10.1.1 *Why hide a struct's fields*.
    * §10.1.3 *Opaque structs*.
    * §10.3 *Exercises*, övning 10.1 - 10.2 - frivilliga extraövningar.

§10.1.3 bygger vidare direkt på kapitel 9, så §10.1.2 kan hoppas över här; den hör till
[L03](../L03/README.md). Bokens opaque `gpio_t` skapas med `gpio_create()`, lektionens med
`gpio_new()`.

---

## Instruktioner

### Förberedelse
* Repetera innehållet i [L01](../L01/README.md).
* Läs §10.1.1 och §10.1.3 i Embedded C.

### Repetition
* Genomför repetitionsuppgiften i [bilaga A](./appendix/a_repetition.md).

### Under lektionen
* Vi slutför först GPIO-drivern i dess nuvarande form.
* Vi modifierar sedan GPIO-drivern så att den använder en opaque struct där attributen är inkapslade.

### Efter lektionen
* Genomför gärna övning 10.1 - 10.2 i Embedded C, §10.3 *Exercises*. Båda besvaras i bokens
appendix B *Answers to the Exercises*.

---

## Lektionsanteckningar
* Lektionsanteckningar finns [här](./notes/README.md).

---

## Utvärdering
* Vad är fördelen med att använda opaque structs jämfört med att definiera struktar i headerfiler?
* Varför fungerar det att enbart fördeklara opaque structs i headerfiler när enbart struktpekare används?

---

## Nästa lektion
* Utökning av GPIO-drivern: Callbacks för interrupts.
* Introduktion till **P01**.

---
