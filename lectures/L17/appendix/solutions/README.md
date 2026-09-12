# Lösningsförslag

Referensimplementationer för övningarna i kursboken, §6.3 *Exercises*.

**OBS!** Försök att lösa övningarna själv innan du tittar på lösningsförslagen.

---

## Lösningsförslag
* **Övningsset 1**:
    * [exercise1.cpp](./exercise1/exercise1.cpp):
        * Arbetartråd med atomisk stoppflagga.
* **Övningsset 2**:
    * [exercise2.cpp](./exercise2/exercise2.cpp):
        * Trådsäker atomisk räknare.
* **Övningsset 3**:
    * [exercise3.cpp](./exercise3/exercise3.cpp):
        * Delat minne skyddat av mutex, med TX- och RX-trådar.
* **Övningsset 4-5**:
    * [driver/counter/interface.hpp](./exercise4-5/include/driver/counter/interface.hpp):
        * Rent virtuellt interface `driver::counter::Interface`.
    * [driver/counter/stub.hpp](./exercise4-5/include/driver/counter/stub.hpp):
        * Trådsäker stub-räknare `driver::counter::Stub` med atomiskt initialiseringstillstånd.
    * [main.cpp](./exercise4-5/source/main.cpp):
        * Demonstrations- och testprogram.
* **Övningsset 6**:
    * [exercise6.cpp](./exercise6/exercise6.cpp):
        * TX/RX-trådar där en condition variable ersätter pollning.
* **Övningsset 7**:
    * [exercise7.cpp](./exercise7/exercise7.cpp):
        * Asynkron firmwarevalidering med `std::async` och `std::future`.

---

## Övningsset 1 – Trådar och atomisk stoppflagga
`workerThread()` tar emot en utskriftshastighet och en atomisk stoppflagga. Den skriver ut ett
meddelande med det angivna intervallet till dess att stoppflaggan sätts. `main()` startar tråden,
sover en stund, sätter flaggan och synkroniserar med `join()`.

---

## Övningsset 2 – Delad räknare med data race
`incrementCounter()` tar emot en räknare och ett antal iterationer. Två trådar inkrementerar samma
räknare samtidigt. Övningarna går igenom tre versioner, och lösningsförslaget är den sista av dem:
* En vanlig `std::uint32_t` som demonstrerar data racen.
* En mutex-skyddad version som åtgärdar den.
* En `std::atomic<std::uint32_t>` som uppnår samma resultat utan mutex.

---

## Övningsset 3 – Delad data skyddad av mutex
`SharedMem` innehåller ett `std::uint16_t`-datavärde och en flagga `newData`. `txThread()` producerar
inkrementerande värden och sätter `newData`; `rxThread()` pollar efter ny data och konsumerar den.
Båda trådarna delar en mutex som skyddar samtliga åtkomster till `SharedMem`. `main()` kör båda
trådarna under en bestämd tid, sätter därefter stoppflaggan och synkroniserar med `join()`.

---

## Övningsset 4–5 – Trådsäker stub-driver
`driver::counter::Interface` definierar ett rent virtuellt interface med `isInitialized()`,
`value()`, `increment()` och `reset()`.

`driver::counter::Stub` implementerar interfacet:
* `myMutex` (`mutable std::mutex`) skyddar `myValue`.
* `myInitialized` (`std::atomic<bool>`) skyddar samtliga räknaroperationer - varje metod returnerar
  tidigt om drivern inte är initialiserad.
* Kopiering och flytt är raderade.

`main()` skapar en `Stub`, startar två trådar via `counterThread()` (100 respektive 200
inkrementeringar), synkroniserar dem och skriver ut slutvärdet - förväntat `300`.

---

## Övningsset 6 – Condition variable
Bygger vidare på övningsset 3. `rxThread()` pollar inte längre med en fördröjning; i stället tar den
en `std::unique_lock` och anropar `cv.wait()` med `hasNewData()` som predikat. `txThread()` anropar
`cv.notify_one()` efter att låset har släppts. `main()` sätter stoppflaggan medan mutexen hålls, så
att den inte kan ändras mellan att mottagaren kontrollerar predikatet och somnar, och anropar
därefter `cv.notify_all()` så att mottagaren vaknar och avslutas ordnat.

---

## Övningsset 7 – std::async och std::future
`validateFirmware()` simulerar en långsam flashläsning genom att sova `2000 ms`, och itererar
därefter över bufferten på jakt efter `0xFFU`. Den startas asynkront via
`std::async(std::launch::async, ...)`. `main()` pollar
`future.wait_for(std::chrono::milliseconds(200U))` mot `std::future_status::ready` i en loop, skriver
ut ett statusmeddelande varje varv, och hämtar därefter resultatet med `future.get()`.

---

## Svar på reflektionsfrågorna

### Övning 1.2
**Vad händer om `join()` inte anropas?**
* `std::thread`-objektet förstörs medan det fortfarande är joinable, vilket anropar
  `std::terminate()` och kraschar programmet.
* Arbetartråden kan hinna avbrytas innan den är klar, när processen avslutas.

**Vilken tråd skriver ut först, huvudtråden eller arbetartråden?**
* Ingen av dem är garanterad att skriva ut först.
* Båda trådarna är körbara så snart arbetartråden har skapats, och det är operativsystemets
  schemaläggare som avgör vilken som körs först.

**Är utskriftsordningen garanterad?**
* Nej. Trådschemaläggning är icke-deterministisk, så ordningen kan skilja sig mellan körningar och
  mellan plattformar.

---

### Övning 1.3
**Varför är `std::atomic<bool>` lämpligt för denna stoppflagga?**
* Den garanterar att läsningar och skrivningar är odelbara och synliga mellan trådar, utan data race.
* Ingen ytterligare synkroniseringsmekanism behövs för en enstaka boolesk flagga som skrivs av en
  tråd och läses av en annan.

**Skulle en vanlig `bool` vara säker här?**
* Nej. Samtidig åtkomst till en vanlig `bool` från flera trådar utan synkronisering är *undefined
  behavior*.
* Kompilatorn eller CPU:n kan dessutom cacha värdet i ett register, så att arbetartråden aldrig ser
  det uppdaterade värdet.

**Varför används `load()` vid läsning av flaggan?**
* `load()` gör den atomiska läsningen explicit och säkerställer att värdet hämtas från det atomiska
  objektet med korrekt minnesordning, inte från en gammal cachad kopia.

**Varför används `store()` vid skrivning av flaggan?**
* `store()` gör den atomiska skrivningen explicit och säkerställer att det nya värdet publiceras till
  samtliga trådar med korrekt minnesordning.

---

### Övning 2.1
**Vilket slutvärde förväntar du dig?**
* `200000`, eftersom var och en av de två trådarna inkrementerar räknaren `100000` gånger.

**Får du alltid det förväntade värdet?**
* Nej. På grund av data racen är resultatet typiskt lägre än `200000` och varierar mellan körningar.

**Varför är detta program osäkert?**
* Två trådar läser, ändrar och skriver samma räknare utan någon synkronisering.
* Sekvensen läs-ändra-skriv är inte atomisk för ett vanligt heltal, så en tråd kan skriva över den
  andras inkrementering.

**Vilket villkor gör detta till en data race?**
* Två eller fler trådar kommer åt samma minnesposition samtidigt, minst en åtkomst är en skrivning,
  och det finns ingen synkronisering mellan dem.

---

### Övning 2.2
**Vilket slutvärde får räknaren nu?**
* Alltid `200000`.

**Varför löser mutexen problemet?**
* Mutexen säkerställer att endast en tråd åt gången kan befinna sig i den kritiska sektionen, vilket
  i praktiken gör sekvensen läs-ändra-skriv atomisk.

**Varför är `std::lock_guard` säkrare än att manuellt anropa `lock()` och `unlock()`?**
* `std::lock_guard` släpper låset automatiskt när den går ur scope, även om ett undantag kastas.
* Manuella `lock()`/`unlock()` riskerar att man glömmer att låsa upp, eller lämnar mutexen låst om
  ett undantag inträffar mellan de två anropen.

---

### Övning 2.3
**Vilket slutvärde får räknaren?**
* Alltid `200000`.

**Varför räcker `std::atomic<std::uint32_t>` i denna övning?**
* Att inkrementera ett enstaka heltal är en oberoende operation. `std::atomic` gör inkrementeringen
  odelbar och trådsäker utan att en mutex behövs.

**Skulle en atomisk räknare fortfarande räcka om flera relaterade variabler måste uppdateras
tillsammans?**
* Nej. Om flera relaterade variabler måste uppdateras som en sammanhållen enhet kan en atomisk typ
  inte i sig skydda den sammansatta operationen.
* En mutex behövs för att uppdateringen av samtliga relaterade variabler ska framstå som atomisk för
  andra trådar.

---

### Övning 3.4
**Varför måste `data` och `newData` skyddas av samma mutex?**
* De hör logiskt ihop - RX måste läsa `data` och `newData` tillsammans, som en sammanhållen
  ögonblicksbild.
* Om de skyddades separat skulle TX kunna uppdatera `data` efter att RX redan har läst `newData`, så
  att RX agerar på ett gammalt eller inkonsekvent värde.

**Varför är `newData` inte atomisk i denna design?**
* `newData` måste kontrolleras och uppdateras tillsammans med `data`, som en sammanhållen enhet.
* Att enbart skydda `newData` med en atomisk variabel skulle inte hindra TX från att uppdatera `data`
  mellan att RX läser flaggan och läser värdet.
* Mutexen skyddar båda fälten tillsammans, vilket gör den sammansatta operationen säker.

**Vad skulle kunna hända om TX uppdaterade `data` och `newData` utan att låsa mutexen?**
* RX skulle kunna läsa `newData = true` innan `data` har skrivits, eller läsa ett delvis uppdaterat
  `data`-värde.
* Detta är en data race och leder till *undefined behavior*.

**Varför är stoppflaggan atomisk i stället för mutex-skyddad?**
* Stoppflaggan är en enstaka boolesk variabel som skrivs av en tråd och läses av andra. Ingen
  sammansatt operation behövs.
* En atomisk boolean räcker och undviker kostnaden av att låsa mutexen varje varv i loopen bara för
  att kontrollera en flagga.

**Skulle `std::atomic<SharedMem>` kunna användas i stället för en mutex?**
* Inte utan ytterligare komplexitet. RX:s operation är en sekvens av läs-ändra-skriv: läs in
  strukten, kontrollera `newData`, nollställ `newData` och skriv tillbaka.
* Även med `std::atomic<SharedMem>` är den sekvensen inte atomisk som helhet. TX skulle kunna skriva
  ett nytt värde mellan RX:s läsning och RX:s skrivning, så att RX tyst skriver över TX:s nya data.
* Att göra det korrekt utan mutex skulle kräva en retry-loop med compare-exchange (CAS) i RX, vilket
  är betydligt mer komplext än mutex-ansatsen.
* Mutexen är rätt verktyg här, eftersom den gör hela den sammansatta operationen säker genom
  mutual exclusion.

---

### Övning 4.3
**Varför måste `value()` låsa mutexen trots att den enbart läser värdet?**
* En annan tråd skulle kunna anropa `increment()` eller `reset()` samtidigt.
* Att läsa `myValue` medan det skrivs är en data race. Mutexen säkerställer att läsningen inte varvas
  med en skrivning.

**Varför är `myMutex` märkt `mutable`?**
* `value()` är en `const`-metod och kan inte modifiera medlemsvariabler.
* Att låsa en mutex är en implementationsdetalj, inte en logisk förändring av objektet.
* `mutable` gör att mutexen kan låsas inne i en `const`-metod utan att bryta mot `const`-korrekthet.

**Vad skulle hända om `increment()` inte låste mutexen?**
* Två trådar skulle kunna läsa samma värde, båda inkrementera det och skriva tillbaka samma resultat,
  så att en inkrementering går förlorad.
* Räknaren skulle landa lägre än förväntat - identiskt med data racen i Övning 2.1.

**Skulle `std::atomic<std::uint32_t>` kunna användas i stället i just denna klass?**
* Ja. I just denna klass verkar varje operation (inkrementera, läsa, återställa) på en enstaka
  variabel oberoende, så `std::atomic<std::uint32_t>` skulle räcka.

**Varför kan en mutex ändå vara att föredra i en mer komplex driver?**
* Om framtida krav tillför fler medlemsvariabler som måste uppdateras tillsammans med `myValue` kan
  en mutex skydda samtliga som en enhet.
* En atomisk variabel kan endast skydda en enstaka variabel; sammansatta operationer över flera
  variabler kräver fortfarande en mutex.

---

### Övning 5.3
**Varför är `myInitialized` lämplig som atomisk variabel?**
* Det är en enstaka boolesk flagga som läses och skrivs oberoende.
* Ingen annan variabel behöver uppdateras i samma atomiska steg, så `std::atomic<bool>` räcker.

**Varför skyddas `myValue` fortfarande av en mutex?**
* `myValue` används av flera operationer (`increment`, `reset`, `value`) som inte får varvas om
  varandra.
* En mutex skyddar samtliga operationer på `myValue` som en grupp, och förhindrar data races.

**Skulle det vara säkert att göra båda variablerna atomiska om framtida krav tillförde mer relaterat
tillstånd?**
* Nej. Om framtida tillstånd måste uppdateras tillsammans med `myValue` som en sammanhållen enhet kan
  atomiska typer inte i sig skydda den sammansatta uppdateringen.
* En mutex skulle behövas för att hålla uppdateringen av samtliga relaterade variabler atomisk som en
  grupp.

**Vad är den huvudsakliga designskillnaden mellan en trådsäker flagga och trådsäker delad data?**
* En trådsäker flagga är en enstaka boolean som endast behöver observeras oberoende - en atomisk
  variabel räcker.
* Trådsäker delad data innebär flera relaterade fält som måste läsas eller skrivas tillsammans som en
  sammanhållen ögonblicksbild, vilket kräver en mutex för att skydda den sammansatta operationen.

**Vad skulle kunna hända om `setInitialized(false)` anropas mellan initialiseringskontrollen och
mutexlåsningen i `increment()`? Hur skulle du åtgärda det?**
* `increment()` skulle passera initialiseringskontrollen, drivern skulle därefter markeras som
  oinitialiserad av en annan tråd, och `increment()` skulle fortsätta och modifiera `myValue` - i
  strid med det avsedda skyddet.
* Åtgärden är att göra kontrollen och uppdateringen till en enda kritisk sektion: kontrollera
  `myInitialized` efter att låset tagits i `increment()` (och likaså i `value()` och `reset()`),
  **och** låta `setInitialized()` ta samma mutex när den ändrar flaggan.
* Att enbart flytta kontrollen in i låset räcker inte: `setInitialized()` låser inte mutexen, så den
  skulle fortfarande kunna ändra flaggan efter att `increment()` har kontrollerat den. Med båda sidor
  under mutexen hinner `setInitialized(false)` antingen klart innan `increment()` kontrollerar
  flaggan, eller väntar till dess att inkrementeringen är gjord.

---

### Övning 6.1
**Varför krävs `std::unique_lock` här i stället för `std::lock_guard`?**
* `cv.wait()` måste låsa upp mutexen medan tråden sover, och låsa den igen när tråden väcks.
* `std::lock_guard` har inget sätt att släppa och återta låset - den stödjer enbart låsning vid
  konstruktion och upplåsning vid destruktion.
* `std::unique_lock` erbjuder `lock()` och `unlock()`, vilket `cv.wait()` använder internt.

**Vad är en spurious wake-up, och hur skyddar predikatet mot den?**
* En spurious wake-up är när `cv.wait()` returnerar trots att varken `notify_one()` eller
  `notify_all()` har anropats, på grund av implementationsdetaljer i operativsystemet.
* Predikatet kontrollerar villkoret på nytt efter varje uppvakning. Om villkoret inte är uppfyllt går
  `wait()` automatiskt tillbaka till att vänta i stället för att fortsätta.

**Varför måste stoppflaggan också kontrolleras inne i predikatet?**
* När stoppflaggan sätts och `notify_all()` anropas vaknar mottagaren.
* Utan `stop.load()` i predikatet skulle mottagaren se `hasNewData() == false`, behandla det som en
  spurious wake-up och somna igen - och aldrig avslutas ordnat.

**Hur skiljer sig denna design från pollningsansatsen i Övning 3.3?**
* I Övning 3.3 vaknar mottagaren var `100 ms` oavsett om data finns tillgänglig, vilket slösar
  CPU-cykler och lägger till upp till `100 ms` latens.
* Med en condition variable sover mottagaren till dess att TX uttryckligen väcker den, vilket minskar
  latensen till nära noll och eliminerar onödig pollning.

**Vad skulle hända om `notify_all()` inte anropades efter att stoppflaggan satts?**
* Mottagartråden skulle förbli blockerad i `cv.wait()` även efter att `stop` satts till `true`,
  eftersom ingenting väcker den.
* Huvudtråden skulle då blockeras för evigt i `join()`, och programmet skulle hänga.

**Varför används `notify_all()` här i stället för `notify_one()`?**
* I denna design finns endast en mottagartråd, så `notify_one()` skulle räcka här.
* `notify_all()` används för korrekthet i det allmänna fallet - om flera trådar väntade på samma
  condition variable skulle `notify_one()` enbart väcka en av dem, och lämna de andra blockerade på
  obestämd tid.

---

### Övning 7.1
**Vad garanterar `std::launch::async` jämfört med att utelämna startpolicyn?**
* `std::launch::async` garanterar att funktionen körs i en ny tråd omedelbart, oberoende av när
  `get()` anropas.
* Utan policyn får implementationen välja `std::launch::deferred`, vilket skjuter upp exekveringen
  till dess att `get()` anropas - och då kör funktionen synkront på den anropande tråden i stället.

**Vid vilken punkt blockeras huvudtråden?**
* Huvudtråden blockeras när `future.get()` anropas.
* Allt mellan `std::async` och `future.get()` exekveras samtidigt som valideringen körs i bakgrunden.

**Vad skulle hända om `future.get()` anropades omedelbart efter `std::async`?**
* Huvudtråden skulle blockeras omedelbart och vänta på att `validateFirmware()` blir klar innan den
  fortsätter.
* Inget samtidigt arbete skulle ske - det skulle bete sig som ett synkront funktionsanrop.

---

### Övning 7.2
**Hur skiljer sig `wait_for()` från `get()`?**
* `wait_for()` väntar högst den angivna tiden och returnerar en status (`ready`, `timeout` eller
  `deferred`) utan att konsumera resultatet eller blockera på obestämd tid.
* `get()` blockerar till dess att resultatet finns tillgängligt, och returnerar det därefter (eller
  kastar om ett undantag), och konsumerar futuren.

**Är det säkert att anropa `get()` efter att `wait_for()` returnerat `std::future_status::ready`?**
* Ja. När `wait_for()` väl returnerar `std::future_status::ready` är resultatet garanterat
  tillgängligt, och `get()` returnerar omedelbart utan att blockera.

---
