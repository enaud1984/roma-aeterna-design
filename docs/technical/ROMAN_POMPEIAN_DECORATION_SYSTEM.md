# Sistema procedurale di decorazione pompeiana

Il core indipendente da Unreal genera `RomanDecorationPlan`, piani di stanza, parete e pavimento, bande, pannelli e palette. La selezione è deterministica per seed, funzione, ricchezza e usura.

Sono supportate famiglie tecniche ispirate ai quattro stili pompeiani: `FirstStyleInspired`, `SecondStyleInspired`, `ThirdStyleInspired`, `FourthStyleInspired`, oltre a `PlainPlaster` e `ServicePlaster`. Non sono copie di ambienti archeologici specifici.

Le pareti sono articolate in zoccolatura, fascia, pannelli, cornice e parte alta. Porte e finestre riservano un intervallo che i pannelli non possono attraversare. La palette resta coerente nella stanza.

Gli asset locali sono creati sotto `Content/LocalAssets/RomaAeterna/Decoration/` e rimangono ignorati. In loro assenza vengono usati materiali tecnici versionati.

Stati: `HISTORICAL_APPROXIMATION`, `FIGURATIVE_FRESCO_ART_NOT_STARTED`, `MANUAL_DECORATION_VISUAL_REVIEW_REQUIRED`.
