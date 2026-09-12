# Tentamen - C++

## Information
Tentamen som täcker:
* Design och implementation av C++-interface (rent virtuella klasser).
* Arv och polymorfism.
* `override`, `final`, `noexcept` och `const`-korrekthet.
* `[[nodiscard]]` på metoder som enbart läser tillstånd, upprepat på överskuggande metoder.
* Headerkonventionen `.hpp` för C++-kod.
* Implementering av stubbklasser (test doubles).
* Radering av copy/move-semantik.
* Smart pointers (`std::unique_ptr`) och modern C++-stil.
* Enkel factory-design.
* Templates och icke-typ-templateparametrar.
* `static_assert` och kompileringstidskontroller.
* Minneshantering med statiskt allokerade arrayer.
* Grundläggande flertrådning (`std::thread`).
* Delad data och trådsäkerhet (race conditions).
* Analys av icke-trådsäker kod samt föreslagna förbättringar.

---

## Övningstentamen
* Följande [övningstentamen](./practice_exam.md) visar vad som ni förväntas kunna.
* Övningstentamen genomförs i helklass under [L18](../lectures/L18/README.md).

---

## Förberedelse
Utöver övningstentamen är lektionernas övningsuppgifter den bästa förberedelsen: samtliga
uppgiftssamlingar i C++-delen har en testsvit, så du får svar på om din lösning gör vad uppgiften ber
om. Kör `make test` från repots rot.

Notera att tentamen skrivs utan kompilator, så det som räknas är vad du kan återskapa på egen hand.
Kursbokens kapitelsammanfattningar är avsedda just för den typen av repetition; se
[litteraturen](../info/README.md#litteratur).

---