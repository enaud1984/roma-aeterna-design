# Validazione delle trasformazioni modulari

Il piano edilizio core usa coordinate locali comprese tra zero e larghezza/profondità. L’attore runtime usa invece il proprio pivot come centro urbano. Il Prompt 29 trattava direttamente le coordinate del piano come coordinate centrate: i moduli risultavano traslati, sovrapposti ad altri edifici o alla strada. La conversione sottrae ora il centro dei bounds del piano prima di creare le istanze.

Le soglie di sicurezza, marcate `HISTORICAL_APPROXIMATION`, sono:

- scala per asse tra 0,01 e 100;
- rapporto massimo tra assi 80:1;
- estensione massima dal mondo 100.000 cm;
- pareti e pavimenti entro 5° da verticale/orizzontale;
- tetti entro 35° di pitch o roll;
- modulo runtime tra 2 e 5.000 cm per asse.

NaN, Infinity, scale nulle o negative, falde implausibili e moduli fuori estensione vengono rifiutati. I gusci accessibili non ricevono più una seconda copia dei blocchi astratti `Wall`, `Floor`, `Roof`, `Door`, `ApartmentDoor` e `ShopOpening`: ciò preserva ingresso, decorazioni e pavimenti. Le falde accessibili usano 8° e una quota calcolata dalla loro semilarghezza.
