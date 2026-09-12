# L04 Testsvit

Enhetstester för allt som kursboken, §1.4 *Exercises*, ber dig skriva, byggda på
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

Varje övningsset är ett eget program och testas därför av en egen binär, som byggs först när den fil
setet efterfrågar finns:

| Binär | Byggs när | Testar |
|---|---|---|
| `language` | **alltid** | Påståenden som §1.2 gör om C++, kontrollerade av kompilatorn |
| `exercise1` | `exercise1/main.cpp` finns | `debug::log` och `app::delay_ms` |
| `exercise2` | `exercise2/driver/timer.hpp` finns | `driver::Timer`, och programmet när `main.cpp` också finns |
| `exercise3` | `exercise3/main.cpp` finns | `swap`, och programmets utskrift |
| `exercise4` | `exercise4/main.cpp` finns | `clear` och `toggle`, och programmets utskrift |

Ett set vars fil ännu inte finns rapporteras som `SKIP`, tillsammans med den sökväg sviten väntar på.
En fil som skrivits under fel namn blir därmed synlig i stället för tyst otestad.

**`language` körs alltid, och det är inte utfyllnad.** `runAllTests()` rapporterar misslyckande när
den inte har några tester att köra, så en svit vars samtliga tester väntade på dina filer skulle vara
röd i en färsk klon och se trasig ut när den enbart var tom. Någonting måste köras från första dagen,
och då kan det lika gärna vara värt att veta: att en `constexpr`-funktion kan ange storleken på en
array, att `auto x{10}` är en `int` i C++17, att ett template instansieras en gång per typ, och att
`std::size_t` är ett annat namn för en typ med fast bredd – vilket är skälet till att `isUnsigned` i
§1.2 inte får specialisera båda.

---

## Hur testerna kommer åt kod i din `main.cpp`

Övningsset 1, 3 och 4 placerar sina funktioner i `main.cpp`, vissa i en anonym namnrymd, som
ingenting utanför den filen kan se. Därför inkluderar testerna din fil:

```cpp
#define main exercise3Main
#include "main.cpp"
#undef main
```

Det gör `swap()` anropbar från testet. Att byta namn på `main` har en sidoeffekt: `main` är den enda
funktion som får utelämna sin `return`, så testet tystar just den varningen för din fil.

**Ditt program körs som det program det är.** Sviten bygger det också för sig självt, med sin egen
`main()`, och testet kör det som en separat process, precis som du skulle göra: det ska avslutas
normalt med returvärdet 0 och skriva ut exakt den förväntade utskriften. En krasch eller ett
returvärde skilt från 0 rapporteras som ett fel. Den omdöpta `main` i den inkluderade kopian anropas
aldrig, och kunde inte anropas säkert: endast den riktiga `::main` får utelämna sin `return`, och
omdöpt faller samma kod ut genom slutet av en helt vanlig funktion, vilket GCC kompilerar till en
fälla.

---

## Vad testerna kontrollerar

**Utskriften, exakt.** Där en övning anger exempelutdata eller förväntad utdata jämför testet det din
kod skriver ut med den, tecken för tecken, och rapporterar den första rad som skiljer sig.
`Sensor failure, log level = 2` och `Sensor failure, level: 2` innehåller båda loggnivån; endast den
första är det övningen ber om.

**Deklarationerna, inte bara beteendet.** `swap()` deklareras `constexpr`, så testet anropar den vid
kompileringstid; en `swap()` som enbart är korrekt går inte att kompilera där, och kompilatorns
meddelande säger varför. Detsamma gäller `noexcept` överallt där en övning ber om det, och
`[[nodiscard]]` på timerns frågemetoder.

**Breda register, som övningen inte använder.** `clear()` och `toggle()` testas på 32- och 64-bitars
register såväl som på det 8-bitars register övningen använder, eftersom `1U << 40` är odefinierat för
en 32-bitars `unsigned` och `static_cast<T>(1U) << 40` är det som gör rätt. En implementation som
klarar övningens exempel med `1U << bit` faller här, genom att nolla den övre halvan av registret.

**Vad som inte får kompilera.** Övning 4.1 ber om en `static_assert` som avvisar ett register av
icke-heltalstyp. `exercise4_rejects_float.cpp` anropar `clear()` på en `float`, och sviten
kontrollerar att det misslyckas *på grund av en statisk assertion*, snarare än att det kompilerar
eller misslyckas av något annat skäl, såsom `&=` på en `float`, vilket också skulle stoppa bygget men
inte säga läsaren någonting.
