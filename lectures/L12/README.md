# L12 - Arbete med **P02**

## Dagordning
* Påbörja implementation av första drivers och stubbar.
* Grundläggande Git för grupparbete.

---

## Mål med lektionen
* Förstå syftet med ett driverbibliotek och varför vi separerar logik från hårdvara.
* Känna till grundläggande kommandon för att skapa brancher, göra commits och pusha kod.

---

## Förutsättningar
* Grundläggande kunskap om klasser och interfaces i C++ (L05–L10).
* ESP-IDF installerat och konfigurerat.

---

## Litteratur
* Referensboken [DevOps](../../info/README.md#litteratur), kapitel 1 *Git and Collaborative Development*:
    * §1.1.3 *A branch-and-pull-request workflow*.
    * §1.1.5 *Code review*.
    * §1.2 *Review* - repetitionsfrågor till hela kapitlet.
    * §1.3 *Exercises*, övningsset *A Feature Branch and a Pull Request* och *Review* - lektionens
    övningar.
* Referensboken [DevOps](../../info/README.md#litteratur), kapitel 3 *Code Formatting and Style Enforcement*:
    * §3.1.1 *The problem formatting solves*.
    * §3.1.2 *clang-format*.
    * §3.1.4 *Enforcing it in CI*.
    * §3.2.3 *The style* - samma `.clang-format` som i detta repo, och den som ska användas i **P02**.
    * §3.3 *Review* - repetitionsfrågor till hela kapitlet.

§3.1.3 *black for Python* kan hoppas över.

---

## Instruktioner

### Förberedelse
* Repetera innehållet i:
    * [L05](../L05/README.md) samt [L06](../L06/README.md) för information om klasser.
    * [L07](../L07/README.md) samt [L08](../L08/README.md) för information arv och interfaces.
* Läs §1.1.3 och §1.1.5 i DevOps.

### Under lektionen
* Läs igenom [uppgiftsbeskrivningen](../../projects/P02/README.md).  
* Ställ frågor vid behov.
* Lägg till detta repos [`.clang-format`](../../.clang-format) i roten av ert repo för **P02**; se
kapitel 3 i DevOps.

### Efter lektionen
* Genomför övningsset *A Feature Branch and a Pull Request* och *Review* i DevOps, §1.3
*Exercises*, i ert repo för **P02**. Samtliga övningar besvaras i bokens appendix A *Answers to the
Exercises*.

---

## Lektionsanteckningar
* De Git-kommandon som behandlades under lektionen finns [här](./notes/git_commands2.md).

---

## Utvärdering
* Vad är syftet med ett driver-interface?
* Vad är skillnaden mellan en stub och en riktig driver?

---

## Nästa lektion
* Factory-mönster.
* Dependency injection via factory.
* Fortsatt arbete med **P02**.

---
