# L17 Testsvit

Enhetstester för allt som kursboken, §6.3 *Exercises*, ber dig skriva, byggda på
ramverket [QAcademy Test](https://github.com/qrtech-academy/test-framework), som ligger utcheckat
som submodulen `libs/test`. Kör `git submodule update --init` en gång om den katalogen är tom.

```bash
make                    # Bygg och kör sviten mot din kod i ../
make SOLUTIONS=1        # Samma tester, mot ../../appendix/solutions
make clean              # Ta bort testbinärerna.
```

`make test` i repots rot kör denna svit och samtliga andra lektioners.

> **Du ska inte skriva några tester i denna kurs.** Testsviten är given och färdig: du skriver din
> lösning på övningarna och kör `make test` för att se om den gör vad övningen ber om. Det här
> dokumentet beskriver vad sviten kontrollerar, så att ett testresultat går att tolka - det är inte
> en uppgift.
>
> Att själv skriva tester kommer i kursen **hårdvarunära testning**. Ordningen är avsiktlig: här får
> du se vad en testsvit är bra för, innan du skriver din första.

---

## Vad som körs, och när

Varje binär byggs med `-pthread`, eftersom samtliga startar trådar.

| Binär | Byggs när | Testar |
|---|---|---|
| `language` | **alltid** | Vad §6.1 påstår om trådar, mutexar, atomics och futures |
| `exercise1` | `exercise1/exercise1.cpp` finns | `workerThread` med atomisk stoppflagga |
| `exercise2` | `exercise2/exercise2.cpp` finns | `incrementCounter` på en atomisk räknare, och programmets utskrift |
| `exercise3` | `exercise3/exercise3.cpp` finns | `SharedMem`, `txThread` och `rxThread` |
| `exercise4-5` | interfacet och stubben i `exercise4-5/include` finns | Räknarinterfacet och den trådsäkra stubben, och programmet när `source/main.cpp` finns |
| `exercise6` | `exercise6/exercise6.cpp` finns | Versionen av set 3 med condition variable |
| `exercise7` | `exercise7/exercise7.cpp` finns | `validateFirmware` via `std::async`, och programmets utskrift |

Ett set vars filer ännu inte finns rapporteras som `SKIP`, tillsammans med den sökväg sviten väntar
på.

**Varje fil växer genom sitt set, och testerna kontrollerar var den landar.** Övningsset 2 slutar med
en atomisk räknare, och det är den versionen som testas - inte den data race som set 2.1 avsiktligt
skapar. Innan du har nått slutet av ett set, förvänta dig att dess tester misslyckas att kompilera
eller rapporterar vad som fortfarande saknas.

---

## Vad testerna kontrollerar

**Vad ett korrekt program garanterar, inte ordningen på utskrifterna.** Trådar körs i den ordning
schemaläggaren väljer, så ett test som krävde en bestämd utskriftsordning skulle vara flakigt även
mot en korrekt lösning. Testerna kontrollerar därför exakta antal (räknaren ska landa på exakt
`200000`, respektive `300`), att trådar stannar när stoppflaggan sätts, och att program avslutas i
stället för att hänga.

**Att programmet faktiskt avslutas.** Varje testbinär körs med en tidsgräns. Ett program som hänger
- en tråd som aldrig synkroniseras, en `wait()` som aldrig notifieras - rapporteras som `FAIL` med
just den frågan, i stället för att blockera bygget.

**Att en tråd som förstörs utan `join()` fångas.** En `std::thread` som varken synkroniseras eller
detacheras anropar `std::terminate()`. Sviten känner igen `SIGABRT` och rapporterar det som vad det
är, med en fråga om orsaken, i stället för som en obegriplig krasch.

**Deklarationerna.** Där en övning ber om `noexcept`, `[[nodiscard]]`, `mutable` eller raderade
kopierings- och flyttoperationer frågar testerna kompilatorn med type traits och `noexcept(...)`.

**Utskriften, där övningen anger den.** `"Worker thread running!"`,
`"Booting system while validating firmware..."` och
`"Still waiting for firmware validation..."` jämförs med det som faktiskt skrivs ut.

---

## Hur testerna kommer åt kod i dina filer

Övningsseten 1, 2, 3, 6 och 7 placerar sina funktioner i en `.cpp`-fil med en egen `main()`, ofta i
en anonym namnrymd. Därför inkluderar testerna din fil med `main` omdöpt, precis som i de tidigare
lektionerna, och kör programmet som en separat process där en utskrift ska kontrolleras.
[`threads.hpp`](./threads.hpp) innehåller hjälpmedlen som testerna använder för att starta och
bevaka trådar.
