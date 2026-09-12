# L09 Testsvit

Enhetstester för allt som kursboken, §3.5 *Exercises*, ber dig skriva, byggda på
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

## Ett program, fyra binärer

Samtliga fyra övningsset i denna lektion bygger ett och samma program, så arbetskatalogen är `../`
självt, med samma struktur som `../../appendix/solutions`: `include/` och `source/` intill denna
katalog. Varje set testas ändå av en egen binär, som byggs så snart det setets filer finns, så
interfacet kan testas innan någon driver är skriven:

| Binär | Byggs när | Testar |
|---|---|---|
| `language` | **alltid** | Påståenden som §3.1 och §3.2 gör om arv och interfaces |
| `exercise1` | `include/driver/serial/interface.hpp` finns | Interfacet, via en testdubblett |
| `exercise2` | `stub.hpp` och `stub.cpp` finns | Stub-drivern |
| `exercise3` | `console.hpp` och `console.cpp` finns | Konsoldrivern, en singleton |
| `exercise4` | `source/main.cpp` och båda drivrutinernas källkod finns | `sendMessage()`, och programmet |

Ett set vars filer ännu inte finns rapporteras som `SKIP`, tillsammans med den sökväg sviten väntar
på. En fil som skrivits under fel namn blir därmed synlig i stället för tyst otestad.

**`language` körs alltid, och det är inte utfyllnad.** `runAllTests()` rapporterar misslyckande när
den inte har några tester att köra, så en svit vars samtliga tester väntade på dina filer skulle vara
röd i en färsk klon. Då kan den lika gärna innehålla något värt att veta: att en klass med en rent
virtuell metod är abstrakt, att det är en virtuell destruktor som gör att radering via en baspekare
förstör det deriverade objektet, att publikt arv gör en `Derived*` till en `Base*` medan privat arv
inte gör det, och att `final` är synligt för kompilatorn.

---

## Vad testerna kontrollerar

**Ett interface, via en testdubblett.** Ett interface kan inte instansieras, så `exercise1_test.cpp`
implementerar det: en minimal klass som överskuggar varje metod med exakt den signatur Övning 1.1
anger. Den kompilerar bara om ditt interface deklarerar dessa metoder, och den överskuggar dem bara om
de är virtuella. Genom den kontrollerar testerna att interfacet är abstrakt, att dess destruktor är
virtuell (genom att radera dubbletten via en pekare till interfacet och räkna destruktoranropen), och
att varje metods returtyp, `const` och `noexcept` är som specificerat.

**Vad en singleton inte kan göra.** Konsolen testas i lika hög grad av vad som är omöjligt som av vad
den gör: den kan inte default-konstrueras, förstöras, kopieras eller flyttas utifrån klassen, och
`instance()` returnerar samma objekt varje gång, som en referens till interfacet. Var och en av dessa
är ett type trait, så en konsol med publik konstruktor, eller en vars kopieringsoperationer aldrig
raderades, faller på ett namngivet test i stället för att kompilera tyst.

En finess är värd att känna till, eftersom testerna hänger på den: att radera flyttoperationerna är i
sig tillräckligt för att även kopieringsoperationerna blir raderade, då en klass som deklarerar en
flyttoperation inte får någon implicit kopiering. En konsol som enbart raderar sina flyttar
rapporteras därför, korrekt, som icke-kopierbar. Boken ber om alla fyra raderingarna ändå, eftersom
att skriva ut dem är tydligare än att förlita sig på regeln.

**Utskriften, exakt.** Konsolen skriver ut det den får, och testet jämför det med de tecken som
skrevs, byte för byte. Programmets utskrift kontrolleras på samma sätt: dess första rad ska vara exakt
`Transmitting data with a serial driver!`, utskriven via konsoldrivern.

**Via interfacet, inte bara direkt.** Stubben används både som en `Stub` och via en referens till
interfacet, och `sendMessage()` testas med en inspelare som sparar varje byte som skrivs till den, så
att ett meddelande som skickas med ett saknat tecken eller en avslutande nollbyte fångas - inte enbart
ett vars sista byte är fel.

**Vad som inte kan testas.** Om en metod är `[[nodiscard]]` går inte att kontrollera med GCC: som L07
§3.2 noterar varnar GCC inte när resultatet av ett virtuellt anrop kastas bort, så ett test som
kastar bort ett sådant kompilerar i vilket fall. `override` kontrolleras via sin effekt: en metod som
var avsedd att överskugga men har fel signatur lämnar stubben abstrakt, och testerna misslyckas då att
kompilera med *cannot declare variable to be of abstract type*.

---

## Hur testerna kommer åt kod i din `main.cpp`

`sendMessage()` ligger i `main.cpp`, som kompileras in i ett program med en egen `main()`, och kan
mycket väl ligga i en anonym namnrymd, som ingenting utanför filen kan se. Därför inkluderar
`exercise4_test.cpp` din fil:

```cpp
#define main exercise4Main
#include "main.cpp"
#undef main
```

Det gör `sendMessage()` anropbar från testet. Att byta namn på `main` har en sidoeffekt: `main` är den
enda funktion som får utelämna sin `return`, så testet tystar just den varningen för din fil.

**Ditt program körs som det program det är.** Sviten bygger det också för sig självt, med sin egen
`main()`, och testet kör det som en separat process, precis som du skulle göra: det ska avslutas
normalt med returvärdet 0 och skriva ut exakt den förväntade utskriften. En krasch eller ett returvärde
skilt från 0 rapporteras som ett fel.
