# L07 - Arv och interfaces (del I)

## Dagordning
* Interfaces (abstrakta klasser med rena virtuella metoder) för att definiera en gemensam uppsättning metoder.
* Arv som ett verktyg för att implementera interfaces.
* Fortsatt arbete med **P01**.

---

## Mål med lektionen
* Kunna skapa interfaces.
* Förstå hur arv används för att implementera interfaces.
* Förstå hur olika implementationer kan användas via samma interface (t.ex. hårdvara vs stubbar).

---

## Förutsättningar
* Grundläggande kännedom om C++ (klasser, constructors, const).

---

## Litteratur
* Kursboken [Modern Embedded C++](../../info/README.md#litteratur), kapitel 3 *Inheritance and Interfaces*:
    * §3.1 *Inheritance in C++*.
    * §3.2 *Interfaces in C++*.
    * §3.3 *Example: An LED Interface in C++* - genomgås som exemplet `cpp_interface`.
* Boken [Embedded C](../../info/README.md#litteratur), kapitel 10 *Encapsulation and Polymorphism in C*:
    * §10.1.6 *Vtables: a `gpio_interface_t` interface* - samma exempel som `c_interface`, med
    delvis andra namn.

---

## Instruktioner

### Förberedelse
* Läs om arv i kursboken, §3.1 *Inheritance in C++*.
* Läs om interfaces i §3.2 *Interfaces in C++*.
* Se gärna följande exempel på implementering av interfaces:
    * Demonstration i C++ [här](./examples/cpp_interface/README.md).
    * Implementation i C för att förstå hur interfaces fungerar [här](./examples/c_interface/README.md).
    Exemplet förklaras i Embedded C, §10.1.6.
* Jämför de två exemplen: C++-varianten använder headerfiler med ändelsen `.hpp`, C-varianten `.h`.
Det är precis den konvention som beskrivs i kursboken, §1.2.

### Under lektionen
* Medverka på genomgång om arv samt interfaces.

### Efter lektionen
* Övningsuppgifterna till detta avsnitt ligger i [L08](../L08/appendix/a_exercises.md) och
kursboken, §3.5 *Exercises*. L09:s uppgifter har en testsvit och körs med `make test`.

---

## Utvärdering
* Vad innebär arv i C++?
* Vad är en abstrakt klass?
* Vad är skillnaden mellan arv och att använda ett interface?
* Varför kan det vara bra att använda ett interface för en GPIO?
* Varför ärvs inte `[[nodiscard]]` av en överskuggande metod, och vad gör man åt det?

---

## Nästa lektion
* Implementation av interfaces för inbyggda system.
* Fortsatt arbete med **P01**.

---