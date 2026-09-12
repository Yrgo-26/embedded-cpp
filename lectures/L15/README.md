# L15 – Templates, type traits och constraints, arbete med **P02**

## Dagordning
* Templates i inbyggda system – fördelar och nackdelar.
* Type traits och compile-time constraints.
* `static_assert()` och säkra API:er (fel vid kompilering i stället för vid körning).
* Fortsatt arbete med **P02**.

---

## Mål med lektionen
* Förstå hur templates genererar kod vid kompilering.
* Kunna använda type traits för att skapa compile-time constraints.
* Förstå varför compile-time-kontroller är särskilt viktiga i inbyggda system.
* Kunna resonera kring när templates är lämpliga – och när de bör undvikas.

---

## Förutsättningar
* Grundläggande kunskap om klasser och funktioner i C++.
* Förståelse för interfaces och polymorfism.
* Grundläggande förståelse för kompilering och länkning.

---

## Litteratur
* Kursboken [Modern Embedded C++](../../info/README.md#litteratur), kapitel 5 *Templates*:
    * §5.1 *Function Templates* och §5.2 *Type Traits and Constraints*.
    * §5.5 *Exercises*, övningsset 1-2 - lektionens övningar.

---

## Instruktioner

### Förberedelse
* Läs kursboken, §5.1 *Function Templates* och §5.2 *Type Traits and Constraints*.
* För ytterligare information, se följande [video tutorial](https://www.youtube.com/watch?v=mbRiN_QmjUY), som behandlar enkla funktionstemplates utan type traits.

### Innan lektionen
* Genomför repetitionsuppgiften i [bilaga A](./appendix/a_repetition.md).

### Under lektionen
* Följ genomgången av templates, type traits och constraints. Fundera på om detta är något ni kan använda i era drivers.
* Arbeta vidare med **P02** efter genomgången.

### Efter lektionen
* Slutför övningarna i kursboken, §5.5 *Exercises*, övningsset 1-2,.
* Skriv dem i [`exercises/`](./exercises/README.md) och kontrollera dem med `make test` från repots
  rot.
* Lösningsförslag finns [här](./appendix/solutions/README.md).

---

## Utvärdering
* Vad är skillnaden mellan compile-time och run-time polymorfism?
* Vad är fördelen med att få ett fel vid kompilering i stället för vid körning?
* Varför kan templates öka binärstorleken?
* När bör man använda templates i stället för interfaces?

---

## Nästa lektion
* Klasstemplates.
* Fortsatt arbete med **P02**.

---
