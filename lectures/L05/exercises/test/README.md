# L05 Testsvit

Enhetstester för allt som kursboken, §2.4 *Exercises*, övningsset 1-3, ber dig skriva, byggda på
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

Varje övningsset är ett eget program och testas därför av en egen binär, som byggs först när de filer
setet efterfrågar finns:

| Binär | Byggs när | Testar |
|---|---|---|
| `language` | **alltid** | Påståenden som §2.1 och §2.2 gör om klasser, kontrollerade av kompilatorn |
| `exercise1` | `exercise1/include/driver/gpio/led.hpp` finns | `Led`; `Button` när `button.hpp` finns; programmet när `main.cpp` också gör det |
| `exercise2` | `exercise2/main.cpp` finns | Programmets utskrift: LED:en som följer knappen, och därefter blinkar |
| `exercise3` | `exercise3/include/driver/buzzer.hpp` och `exercise3/source/driver/buzzer.cpp` finns | `Buzzer`, och programmet när `source/main.cpp` finns |

Ett set vars filer ännu inte finns rapporteras som `SKIP`, tillsammans med den sökväg sviten väntar
på. En fil som skrivits under fel namn blir därmed synlig i stället för tyst otestad. Övningsset 1 och
2 är separata binärer trots att de använder samma klasser: varje set har sin egen kopia av `led.hpp`
och `button.hpp`, och en binär som innehöll två olika definitioner av `driver::gpio::Led` skulle vara
ett brott mot ODR snarare än ett test.

**`language` körs alltid, och det är inte utfyllnad.** `runAllTests()` rapporterar misslyckande när
den inte har några tester att köra, så en svit vars samtliga tester väntade på dina filer skulle vara
röd i en färsk klon och se trasig ut när den enbart var tom. Den innehåller bilagornas påståenden om
klasser, i en form kompilatorn kan bekräfta eller det körande programmet kan visa: att en strukts
medlemmar är publika och en klass' privata som standard, att `ledPrint(8U)` kompilerar och skriver ut
en LED som aldrig skapades ända till konstruktorn görs `explicit`, att en statisk medlem räknar
instanser över samtliga objekt, att en `static constexpr`-medlem kan ange storleken på en array, att
en `const`-medlem utesluter tilldelning men inte kopiering, och att `std::move()` faller tillbaka på
kopiering i en klass som deklarerar en destruktor, eftersom en sådan klass inte får någon
flyttkonstruktor av kompilatorn.

---

## Hur testerna kör ditt program

Programmens utskrift är en del av varje övning, så sviten bygger varje sets program för sig självt,
på samma sätt som din Makefile gör: från `main.cpp`, och för övningsset 3 från `source/main.cpp` samt
samtliga filer i `source/driver/`. Testet kör det som en separat process: det ska avslutas normalt med
returvärdet 0 och skriva ut exakt exempelutdatan. En krasch eller ett returvärde skilt från 0
rapporteras som ett fel. Klasserna själva testas direkt, genom att deras headerfiler inkluderas och
`source/driver/` kompileras in i testet.

---

## Vad testerna kontrollerar

**Deklarationerna, inte bara beteendet.** Det mesta som övningarna ber om är en deklaration:
`explicit`, `noexcept`, `final`, `[[nodiscard]]`, en destruktor som är `default`, raderade
kopierings- och flyttoperationer. Var och en är synlig för kompilatorn, så testerna frågar den, med
type traits såsom `std::is_convertible<std::uint8_t, Led>` (falskt när konstruktorn är `explicit`) och
`noexcept(led.on())`. En klass som beter sig korrekt men utelämnar en av dem faller.

**En defaultad destruktor, inte enbart en tom.** `~Led() noexcept = default;` lämnar `Led` trivialt
destruerbar; `~Led() noexcept {}` gör det inte, trots att den inte heller gör någonting. Testet
kontrollerar `std::is_trivially_destructible`, vilket är hur "markera den `default`" blir något ett
test kan se.

**Raderade operationer, så som kompilatorn ser dem.** Testerna kontrollerar att klassen inte kan
default-konstrueras, kopieras eller flyttas, oavsett hur du ordnar det. Att radera någon av
flyttoperationerna gör redan att kompilatorn raderar den implicita kopieringskonstruktorn, så en klass
som glömmer en radering men behåller en annan kan ändå passera; en som glömmer dem alla gör det inte.

**Utskriften, exakt.** Där en övning anger exempelutdata jämför testet det din kod skriver ut med den,
tecken för tecken, och rapporterar den första rad som skiljer sig. Det inkluderar destruktorerna:
buzzerns meddelande om frigjorda resurser, med sitt eget pin-nummer.
