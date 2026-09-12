# Hårdvarunära programmering C/C++
Repo för kursen **Hårdvarunära programmering C/C++** med klassen Ee26, vt27.

## Om kursen
Kursen behandlar utveckling av inbyggda system med fokus på:
* Embedded systemarkitektur.
* Drivrutinsdesign för mikrokontrollers (t.ex. AVR och ESP32).
* Gradvis övergång från C till modern C++ (C++17).
* Abstraktion och lagerindelning (HAL, systemlogik, applikationslager).
* Objektorienterad design i resursbegränsade system.
* Testbar och modulär kodstruktur.
* Grundläggande designmönster för embedded-system.

Under kursens gång implementeras:
* GPIO- och timer-drivrutiner i C.
* Motsvarande implementationer i C++ med klasser och interface.
* Systemlogik ovanpå hårdvaruabstraktioner.
* Ett mindre driverbibliotek för ESP32.
* Tillämpning av templates, smarta pekare och synkroniseringsmekanismer.

Konventioner i kursens C++-kod:
* Headerfiler i C++ ges ändelsen `.hpp`; headerfiler i C behåller `.h`.
* Metoder som enbart läser tillstånd märks `const`, `noexcept` och `[[nodiscard]]`.
* Klasser som representerar en unik hårdvaruresurs får sin kopierings- och flyttsemantik raderad.
* Heltalstyper med fast bredd (`std::uint8_t`, `std::uint16_t`, ...) i stället för `unsigned`.
* Namngivna `constexpr`-konstanter i stället för magiska tal.
* Antingen `typ x{värde}` eller `auto x = värde`; `auto` blandas aldrig med klammerinitialisering.

Efter genomförd kurs ska studenten kunna:
* Implementera hårdvarunära kod med tydliga interfaces.
* Separera hårdvara från systemlogik.
* Skriva robust, läsbar och underhållbar embedded C++.
* Resonera kring arkitekturval och abstraheringsnivåer.

---

## Boken
Kursens huvudbok, på engelska:
* [Modern Embedded C++](https://github.com/qrtech-academy/modern-embedded-cpp/blob/main/book/modern-embedded-cpp.pdf).

Den täcker C++-delen i sex kapitel, från övergången från C till modern C++ till flertrådning, och
är kursens enda text för den delen. Varje lektions README anger vilket kapitel och vilka avsnitt som
hör till lektionen; se [kapitelöversikten](./info/README.md#litteratur). 

Till övningarna finns testsviter och lösningsförslag i det här repot; se
[Kontrollera ditt arbete](#kontrollera-ditt-arbete). 

### Referenslitteratur
Två böcker används som referenslitteratur, också de på engelska:
* [Embedded C](https://github.com/qrtech-academy/embedded-c/blob/main/book/embedded-c.pdf).
* [DevOps](https://github.com/qrtech-academy/devops/blob/main/book/devops.pdf).

De används så här:
* **Embedded C**:
    * Grunderna i C och i registernära programmering av ATmega328P, som kursen förutsätter, finns
      här; se [förkunskaper](./info/README.md#förkunskaper) för vilka kapitel som täcker vad.
    * De två sista kapitlen, om struktar som drivrutiner och inkapsling i C, hör till C-delen i
      **L01**-**L03**.
* **DevOps**:
    * Kapitel 1-3, om Git, repo-organisation och kodformatering, används när grupprojektet **P02**
      startar i **L11** och **L12**.

---

## Kontrollera ditt arbete
Till varje uppgiftssamling i C++-delen finns en **färdig testsvit**. Klona repot tillsammans med
testramverket, som är en submodul:

```bash
git clone --recursive <repo-url>
```

(I en klon som gjorts utan `--recursive`, kör `git submodule update --init` en gång.) Skriv dina
lösningar i `lectures/LNN/exercises`, där varje lektions README anger vilken fil som ska ligga var,
och kör:

```bash
make test               # Samtliga lektioners tester, mot din kod.
make test SOLUTIONS=1   # Samma tester, mot lösningsförslagen.
make build              # Bygg samtliga kodexempel i föreläsningsmaterialet.
```

En uppgiftssamling du inte har börjat på rapporteras som `SKIP`, tillsammans med den fil testerna
väntar på. Där en övning anger exempelutdata jämför testerna ditt programs utskrift med den, tecken
för tecken.

**Du skriver inga tester själv i denna kurs** - testsviterna är givna. Att skriva tester kommer i
kursen hårdvarunära testning.

---

## Struktur

```text
ci/          Skript för bygge, test och formatkontroll
exam/        Tentameninformation och övningstentamen
info/        Kursinformation, schema, litteratur och examination
lectures/    Föreläsningar, bilagor, övningsuppgifter och testsviter
libs/        Testramverket (submodul) samt kursens teststöd
projects/    Projektbeskrivningar, krav och inlämningsinstruktioner
```

---
