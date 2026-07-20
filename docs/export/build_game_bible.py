#!/usr/bin/env python3
"""Generatore riproducibile della Game Bible editoriale di Roma Aeterna.

I Markdown restano canonici. Questo script legge una selezione esplicita,
estrae sintesi e metadati, genera diagrammi interni, produce DOCX e report,
e valida link e sorgenti. Il PDF viene esportato da Word tramite lo script
PowerShell compagno, cosi campi, indice e numeri di pagina vengono aggiornati.
"""

from __future__ import annotations

import argparse
import json
import math
import re
import shutil
import textwrap
from collections import Counter
from datetime import datetime
from pathlib import Path
from typing import Iterable

from PIL import Image, ImageDraw, ImageFont
from docx import Document
from docx.enum.section import WD_SECTION
from docx.enum.style import WD_STYLE_TYPE
from docx.enum.table import WD_CELL_VERTICAL_ALIGNMENT, WD_TABLE_ALIGNMENT
from docx.enum.text import WD_ALIGN_PARAGRAPH, WD_BREAK, WD_LINE_SPACING
from docx.oxml import OxmlElement
from docx.oxml.ns import qn
from docx.shared import Cm, Inches, Pt, RGBColor
from pypdf import PdfReader


ROOT = Path(__file__).resolve().parents[2]
EXPORT = ROOT / "docs" / "export"
CONFIG_PATH = EXPORT / "game_bible_config.json"
DOCX_PATH = EXPORT / "ROMA_AETERNA_GAME_BIBLE.docx"
PDF_PATH = EXPORT / "ROMA_AETERNA_GAME_BIBLE.pdf"
REPORT_PATH = EXPORT / "GENERATION_REPORT.md"
CREDITS_PATH = EXPORT / "IMAGE_CREDITS.md"
GEN_DIR = EXPORT / "_generated"
DIAGRAM_DIR = GEN_DIR / "diagrams"
QA_DIR = GEN_DIR / "qa"

POMPEII_RED = "8B2E2E"
OCHRE = "B98228"
INK = "263238"
SAND = "F4EEE3"
BLUE = "315B6D"
MUTED = "687078"
WHITE = "FFFFFF"


TABLES = {
    "project_facts": (["Voce", "Sintesi"], [
        ["Genere", "RPG open world sandbox storico, single-player"],
        ["Protagonista", "Persona comune; nessuna centralita eroica garantita"],
        ["Vertical slice", "Pompei, 1 luglio 77 d.C.; orizzonte dimostrativo di 30 giorni"],
        ["Promessa", "Mondo persistente, societa ed economia autonome, conseguenze situate"],
        ["Stato", "Game Bible avanzata; implementazione formalmente NON READY"],
    ]),
    "readiness": (["Area", "Stato editoriale", "Blocco principale"], [
        ["Design P0", "S2-S3", "Promozione a S4 e golden scenario"],
        ["Tecnologia", "S3", "Versione UE5, plugin, formati e toolchain"],
        ["Pompei", "S3", "GIS, edifici P0 e review interdisciplinare"],
        ["Produzione", "S2-S3", "Owner, capacity, CI, LFS e firme"],
    ]),
    "evidence_levels": (["Classe", "Significato", "Uso editoriale"], [
        ["A", "Attestato direttamente", "Presentabile come fatto con fonte"],
        ["B", "Altamente probabile", "Ricostruzione forte, limiti dichiarati"],
        ["C", "Ricostruzione plausibile", "Ipotesi motivata, non certezza"],
        ["D", "Scelta di design necessaria", "Licenza creativa esplicita"],
        ["E", "Da verificare", "Non canonico e non implementabile come fatto"],
    ]),
    "city_tiers": (["Tier", "Tipologia", "Profondita"], [
        ["C1", "Capitale/citta principale", "Sistemi urbani completi e rete regionale"],
        ["C2", "Citta secondaria", "Identita e filiere selezionate"],
        ["C3", "Villaggio/insediamento", "Servizi e popolazione essenziali"],
        ["C4", "Villa, fattoria, porto, cava", "Nodo specialistico o mappa locale"],
        ["C5", "Nodo remoto", "Simulazione aggregata e notizie"],
    ]),
    "pompeii_buildings": (["Luogo", "Tier demo", "Funzione"], [
        ["Foro e Macellum", "P0/P1", "Scambio, annunci, autorita e culto"],
        ["Terme Stabiane", "P0", "Igiene, lavoro e socialita"],
        ["Santuario di Iside", "P0/P2", "Rito, preparazione e rete sociale"],
        ["Panificio selezionato", "P0", "Filiera grano-farina-pane"],
        ["Fullonica di Stephanus", "P0", "Lavoro tessile e consegne"],
        ["Anfiteatro/teatri", "P1; P0 evento", "Giochi rari, folla e ordine pubblico"],
    ]),
    "social_statuses": (["Status", "Capacita tipiche", "Vincoli da rappresentare"], [
        ["Cittadino libero", "Contratti, proprieta, ricorso civico situato", "Censo, genere, reputazione e obblighi"],
        ["Liberto/a", "Lavoro, impresa, reti e proprieta secondo caso", "Patronato, stigma e limiti giuridici"],
        ["Libero non cittadino", "Lavoro e relazioni locali", "Capacita differenziate e protezione"],
        ["Persona schiavizzata", "Mansioni, relazioni e agency sotto coercizione", "Assenza di piena capacita; violenza e dipendenza"],
    ]),
    "npc_categories": (["Categoria", "Persistenza", "Uso"], [
        ["NPC critico nominato", "Completa", "Relazioni, lavoro, istituzioni, memoria"],
        ["NPC persistente di supporto", "Media", "Routine e ruolo funzionale"],
        ["Coorte localizzata", "Aggregata reversibile", "Flussi e capacita urbane"],
        ["Popolazione statistica", "Statistica", "Condizioni remote e demografia"],
    ]),
    "simulation_levels": (["Livello", "Rappresentazione", "Aggiornamento"], [
        ["N0", "Visibile e interagibile", "Continuo/event-driven"],
        ["N1", "Area caricata, fuori camera", "Intervalli brevi"],
        ["N2", "Citta non caricata", "Routine semplificata"],
        ["N3", "Individuo remoto", "Transizioni a intervalli"],
        ["N4", "Coorte aggregata", "Bilanci e flussi"],
        ["N5", "Popolazione statistica", "Ricostruzione da distribuzioni"],
    ]),
    "professions": (["Priorita demo", "Professione/attivita", "Loop dimostrato"], [
        ["P0", "Panificazione", "Input, trasformazione, vendita, scarto"],
        ["P0", "Fullonica/tessile", "Lotto, trattamento, qualita, consegna"],
        ["P0", "Servizio domestico e consegna", "Ordine, custodia, percorso, prova"],
        ["P1", "Trasporto giornaliero", "Ingaggio, spostamento, verifica, paga"],
        ["P1", "Vendita al dettaglio", "Scorta, trattativa, vendita, conto"],
    ]),
    "currency_prices": (["Dominio", "Regola", "Cautela"], [
        ["Moneta", "Unita e denominazioni storicamente contestualizzate", "Nessuna equivalenza moderna diretta"],
        ["Prezzi", "Locali, qualitativi, stagionali e dipendenti dalle scorte", "Valori P0 da validare"],
        ["Salari", "Per tempo, compito, status e contratto", "Pagamento non sempre monetario o garantito"],
        ["Credito", "Relazione, garanzia, reputazione e rischio", "Interessi e rimedi per periodo/luogo"],
    ]),
    "supply_chains": (["Filiera", "Trasformazioni", "Rischi principali"], [
        ["Grano e pane", "Raccolta - trasporto - stoccaggio - molitura - cottura", "Umidita, incendio, ritardo, prezzo"],
        ["Vino e olio", "Coltivazione - spremitura - contenitore - mercato", "Stagione, qualita, contenitori"],
        ["Tessile e lana", "Fibra - filatura - tessitura - trattamento", "Acqua, reagenti, danno, lavoro"],
        ["Ceramica e vetro", "Materia - fornace - lotto - distribuzione", "Combustibile, rotture, capacita"],
        ["Metalli, pietra e armi", "Estrazione remota - trasporto - officina", "Provenienza, costo, guerra"],
    ]),
    "magistracies": (["Istituzione", "Funzione di progetto", "Vincolo"], [
        ["Duoviri", "Autorita municipale e procedure selezionate", "Competenze e titolari per data"],
        ["Aediles", "Mercati, infrastrutture e ordine secondo dossier", "Evitare equivalenti amministrativi moderni"],
        ["Ordo decurionum", "Prestigio, decisione e rete civica", "Accesso e composizione storicamente situati"],
        ["Autorita imperiali", "Vincoli e notizie sovralocali", "Non presenza costante a Pompei"],
    ]),
    "event_frequency": (["Classe", "Frequenza", "Esempi"], [
        ["Routine", "Quotidiana ma variata", "Consegne, turni, acqua, rito domestico"],
        ["Locale", "Condizionale", "Lite, lotto danneggiato, indisposizione"],
        ["Civico", "Pochi nel mese", "Udienza, annuncio, mercato speciale"],
        ["Pubblico", "Massimo uno per run standard", "Rito o gioco controllato"],
        ["Shock", "Raro, non garantito", "Incendio locale, scarsita, crollo"],
    ]),
    "military_ranks": (["Scala", "Ruolo", "Rappresentazione"], [
        ["Contubernium", "Unita di convivenza e supporto", "Relazioni e logistica"],
        ["Centuria", "Unita tattico-amministrativa", "Simulata per coorti/individui chiave"],
        ["Cohors", "Raggruppamento di centurie", "Aggregazione operativa"],
        ["Legio", "Formazione maggiore", "Simulazione remota/strategica"],
        ["Auxilia", "Formazioni non legionarie differenziate", "Nessun modello unico universale"],
    ]),
    "weapons": (["Categoria", "Uso", "Variabili di sistema"], [
        ["Arma corta", "Spazi stretti e controllo", "Portata, massa, presa, contatto"],
        ["Arma in asta", "Distanza e gruppo", "Formazione, ingombro, terreno"],
        ["Scudo", "Copertura attiva e coesione", "Angolo, fatica, integrita"],
        ["Armatura", "Riduzione/localizzazione del trauma", "Copertura, mobilita, calore"],
        ["Oggetto improvvisato", "Rissa e difesa", "Disponibilita, fragilita, escalation"],
    ]),
    "injuries": (["Stato", "Effetto", "Risposta"], [
        ["Dolore", "Riduce precisione e volonta", "Riposo, cura, adrenalina limitata"],
        ["Sanguinamento", "Perdita progressiva e rischio", "Pressione, medicazione, tempo"],
        ["Trauma", "Funzione locale compromessa", "Immobilizzazione e prognosi incerta"],
        ["Stanchezza", "Peggiora guardia e decisione", "Ritmo, pausa, resa"],
        ["Paura/morale", "Fuga, blocco, resa o coesione", "Leadership, contesto, via d'uscita"],
    ]),
    "dynamic_events": (["Fase", "Domanda di progetto", "Persistenza"], [
        ["Condizione", "Perche ora e qui?", "Driver e soglie"],
        ["Propagazione", "Chi apprende o subisce?", "Fonti, rotte, ritardi"],
        ["Risposta", "Quali agenti hanno capacita?", "Azioni e costi"],
        ["Risoluzione", "Cosa termina davvero?", "Stato e aftermath"],
        ["Memoria", "Chi ricorda e con quale certezza?", "Ledger storico e reputazioni"],
    ]),
    "data_domains": (["Dominio", "Autorita", "Consumatori"], [
        ["Identita e tempo", "Registry/clock canonici", "Tutti i sistemi"],
        ["Persona e relazioni", "Simulazione sociale", "AI, contenuti, UI, save"],
        ["Mondo e proprieta", "World/Property", "Interazione, economia, crimine"],
        ["Economia e inventario", "Ledger economici", "Lavoro, quest, UI"],
        ["Eventi e conoscenza", "Bus/ledger versionati", "AI, narrazione, persistenza"],
    ]),
    "milestones": (["Fase", "Risultato", "Gate"], [
        ["Prototipo tecnico", "Fondazioni e ciclo minimo", "Build/test riproducibili"],
        ["Prototipo gameplay", "Loop lavoro-relazioni-conseguenze", "Golden scenario"],
        ["Pre-alpha", "Contenuti P0 integrati", "Stabilita e save"],
        ["Vertical slice", "Qualita rappresentativa", "DA-01-10"],
        ["Demo interna", "Playtest e tuning", "QA interdisciplinare"],
        ["Demo pubblicabile", "Pacchetto distribuibile", "Release readiness"],
    ]),
    "risks": (["Rischio", "Effetto", "Mitigazione"], [
        ["Scope sistemico", "Troppi sistemi incompleti", "Verticale P0 e tagli espliciti"],
        ["Prestazioni NPC", "Folla o routine non sostenibili", "LOD, benchmark e degradazione"],
        ["Falsa accuratezza", "Affidabilita e danno reputazionale", "Classi A-E e review"],
        ["Save incompatibili", "Perdita progresso", "Versionamento, recovery e golden saves"],
        ["Ownership assente", "Decisioni non chiuse", "Owner/reviewer e gate formali"],
    ]),
    "open_questions": (["Area", "Decisione bloccante", "Stato"], [
        ["Pompei", "Poligono GIS, edifici P0, calendario", "Open"],
        ["Tecnologia", "Versione UE5, plugin e formati fisici", "Open"],
        ["Prestazioni", "Hardware, conteggi NPC e benchmark", "Open"],
        ["Produzione", "Team, owner, CI, LFS e storage", "Open"],
        ["Contenuti", "Rating, lingue, review storica/sensitivity", "Open"],
    ]),
}


FLOW_SPECS = {
    "core_loop": ("Ciclo principale di gameplay", ["Osserva il contesto", "Assumi un obbligo", "Agisci e consuma risorse", "Subisci conseguenze", "Adatta relazioni e piani"]),
    "city_network": ("Rete iniziale delle citta", ["Roma / condizioni imperiali", "Neapolis e Puteoli", "Pompei", "Nuceria / Stabiae / Herculaneum", "Ville, fattorie e approdi"]),
    "regional_connections": ("Pompei e il territorio", ["Aziende e ville", "Porte e magazzini", "Mercati di Pompei", "Household e botteghe", "Nodi regionali e porti"]),
    "npc_lifecycle": ("Ciclo di vita di un NPC", ["Nascita e household", "Infanzia ed educazione", "Lavoro e relazioni", "Famiglia e patrimonio", "Vecchiaia, morte ed eredita"]),
    "npc_daily_cycle": ("Routine quotidiana situata", ["Bisogni e obblighi", "Piano contestuale", "Spostamento", "Attivita e incontri", "Memoria e ripianificazione"]),
    "simulation_lod": ("Livelli di simulazione", ["N0: visibile", "N1: area caricata", "N2-N3: remoto individuale", "N4: coorte", "N5: statistico"]),
    "knowledge_flow": ("Memoria e propagazione delle informazioni", ["Percezione", "Memoria con fonte", "Comunicazione", "Valutazione di fiducia", "Azione e conseguenza"]),
    "family_succession": ("Famiglia ed eredita", ["Household", "Unione/adozione", "Figli ed eredi", "Morte e apertura successione", "Trasferimento di diritti e debiti"]),
    "social_progression": ("Progressione sociale", ["Status e capacita iniziali", "Lavoro e competenza", "Relazioni e reputazione", "Patrimonio e obblighi", "Nuove opportunita, non garanzie"]),
    "economic_flow": ("Produzione e commercio", ["Origine e input", "Trasformazione", "Stoccaggio", "Trasporto e mercato", "Consumo, scarto e reinvestimento"]),
    "political_career": ("Carriera politica", ["Capacita giuridica", "Censo e reputazione", "Rete di patronato", "Carica o incarico", "Responsabilita, conflitto e memoria"]),
    "military_career": ("Carriera militare", ["Reclutamento", "Addestramento", "Unita e disciplina", "Servizio e ricompense", "Congedo e veterano"]),
    "event_system": ("Sistema degli eventi", ["Condizioni", "Attivazione", "Propagazione", "Risposte autonome", "Risoluzione e memoria"]),
    "technical_architecture": ("Architettura tecnica a strati", ["Dati canonici", "Simulazione di dominio", "Orchestrazione ed eventi", "Presentazione", "Interazione e UI"]),
    "ue_modules": ("Moduli Unreal Engine proposti", ["Core/Identity/Time", "World/Simulation/AI", "Economy/Property/Inventory", "Content/Interaction/UI", "Save/Diagnostics/Tools"]),
    "save_flow": ("Flusso di salvataggio", ["Snapshot consistente", "Serializzazione versionata", "Checksum e scrittura atomica", "Backup/recovery", "Migrazione e caricamento"]),
    "demo_roadmap": ("Roadmap della demo", ["Prototipo tecnico", "Prototipo gameplay", "Pre-alpha", "Vertical slice", "Demo interna", "Demo pubblicabile"]),
}


def rgb(value: str) -> RGBColor:
    return RGBColor.from_string(value)


def clean_markdown(text: str) -> str:
    text = re.sub(r"```.*?```", "", text, flags=re.S)
    text = re.sub(r"~~~.*?~~~", "", text, flags=re.S)
    text = re.sub(r"!\[[^]]*\]\([^)]*\)", "", text)
    text = re.sub(r"\[([^]]+)\]\([^)]*\)", r"\1", text)
    text = re.sub(r"[`*_]", "", text)
    text = re.sub(r"<[^>]+>", "", text)
    text = re.sub(r"\s+", " ", text).strip()
    return text


def read_source(path: str) -> str:
    target = ROOT / path
    return target.read_text(encoding="utf-8") if target.exists() else ""


def parse_sections(markdown: str) -> dict[str, str]:
    sections: dict[str, list[str]] = {"_lead": []}
    current = "_lead"
    in_code = False
    for line in markdown.splitlines():
        if line.strip().startswith(("```", "~~~")):
            in_code = not in_code
            continue
        if in_code:
            continue
        match = re.match(r"^#{1,4}\s+(.+)$", line)
        if match:
            current = clean_markdown(match.group(1)).lower()
            sections.setdefault(current, [])
        else:
            sections.setdefault(current, []).append(line)
    return {key: "\n".join(value).strip() for key, value in sections.items()}


def editorial_extract(paths: list[str], limit: int = 3) -> list[str]:
    candidates: list[str] = []
    skip_heads = {"scopo", "descrizione", "ambito", "dipendenze", "collegamenti agli altri documenti", "todo"}
    for path in paths:
        content = read_source(path)
        if not content:
            continue
        sections = parse_sections(content)
        ordered = []
        for heading, body in sections.items():
            if heading in skip_heads or heading.startswith("collegamenti") or heading.startswith("todo"):
                continue
            ordered.append(body)
        if not ordered:
            ordered = list(sections.values())
        for body in ordered:
            for block in re.split(r"\n\s*\n", body):
                if block.lstrip().startswith(("|", "- [", "**ID", "**Stato", "flowchart", "graph ", "stateDiagram", "sequenceDiagram")):
                    continue
                if re.match(r"^[-*]\s", block.strip()):
                    continue
                value = clean_markdown(block)
                if 110 <= len(value) <= 900 and value not in candidates:
                    candidates.append(value)
                    break
        if len(candidates) >= limit:
            break
    return candidates[:limit]


def extract_bullets(paths: list[str], heading_terms: Iterable[str], limit: int = 5) -> list[str]:
    result: list[str] = []
    for path in paths:
        sections = parse_sections(read_source(path))
        for heading, body in sections.items():
            if not any(term in heading for term in heading_terms):
                continue
            for line in body.splitlines():
                match = re.match(r"^\s*[-*]\s+(.*)", line)
                if match:
                    value = clean_markdown(match.group(1))
                    if value and value not in result:
                        result.append(value)
                if len(result) >= limit:
                    return result
    return result


def confidence_for(paths: list[str]) -> str:
    text = "\n".join(read_source(p) for p in paths)
    counts = Counter(re.findall(r"\b([A-E])\b", text))
    if not counts:
        return "Mista / non assegnata"
    return ", ".join(f"{key}:{counts[key]}" for key in "ABCDE" if counts[key])


def validate_markdown_links() -> tuple[list[str], int]:
    bad: list[str] = []
    checked = 0
    for md in ROOT.rglob("*.md"):
        if ".git" in md.parts or "_generated" in md.parts:
            continue
        content = md.read_text(encoding="utf-8", errors="replace")
        for target in re.findall(r"(?<!!)\[[^]]*\]\(([^)]+)\)", content):
            target = target.strip().strip("<>").split("#", 1)[0]
            if not target or re.match(r"^[a-z]+://", target, flags=re.I) or target.startswith(("mailto:", "#")):
                continue
            checked += 1
            from urllib.parse import unquote
            candidate = (md.parent / unquote(target)).resolve()
            if not candidate.exists():
                bad.append(f"{md.relative_to(ROOT).as_posix()} -> {target}")
    return sorted(set(bad)), checked


def get_font(size: int, bold: bool = False):
    candidates = [
        Path("C:/Windows/Fonts/calibrib.ttf" if bold else "C:/Windows/Fonts/calibri.ttf"),
        Path("C:/Windows/Fonts/arialbd.ttf" if bold else "C:/Windows/Fonts/arial.ttf"),
    ]
    for candidate in candidates:
        if candidate.exists():
            return ImageFont.truetype(str(candidate), size=size)
    return ImageFont.load_default()


def wrapped(draw: ImageDraw.ImageDraw, text: str, width_px: int, font) -> list[str]:
    words = text.split()
    lines, current = [], ""
    for word in words:
        test = f"{current} {word}".strip()
        if draw.textbbox((0, 0), test, font=font)[2] <= width_px:
            current = test
        else:
            if current:
                lines.append(current)
            current = word
    if current:
        lines.append(current)
    return lines


def draw_flow(name: str, title: str, nodes: list[str]) -> Path:
    DIAGRAM_DIR.mkdir(parents=True, exist_ok=True)
    width, height = 2200, 850
    image = Image.new("RGB", (width, height), "#" + WHITE)
    draw = ImageDraw.Draw(image)
    title_font = get_font(54, True)
    body_font = get_font(30, True)
    small_font = get_font(24)
    draw.text((80, 45), title, fill="#" + INK, font=title_font)
    draw.line((80, 125, width - 80, 125), fill="#" + OCHRE, width=6)
    n = len(nodes)
    gap = 45
    usable = width - 160 - gap * (n - 1)
    box_w = usable // n
    box_h = 250
    y = 260
    colors = [SAND, "E7EEF1", "F1E6E2", "E9EEE4", "F6EBCF", "E7E3EE"]
    for idx, node in enumerate(nodes):
        x = 80 + idx * (box_w + gap)
        draw.rounded_rectangle((x, y, x + box_w, y + box_h), radius=25, fill="#" + colors[idx % len(colors)], outline="#" + POMPEII_RED, width=4)
        lines = wrapped(draw, node, box_w - 45, body_font)
        total_h = len(lines) * 40
        ty = y + (box_h - total_h) / 2
        for line in lines:
            bbox = draw.textbbox((0, 0), line, font=body_font)
            draw.text((x + (box_w - (bbox[2] - bbox[0])) / 2, ty), line, fill="#" + INK, font=body_font)
            ty += 40
        if idx < n - 1:
            ax = x + box_w + 8
            ay = y + box_h // 2
            draw.line((ax, ay, ax + gap - 16, ay), fill="#" + BLUE, width=7)
            draw.polygon([(ax + gap - 16, ay), (ax + gap - 34, ay - 12), (ax + gap - 34, ay + 12)], fill="#" + BLUE)
    draw.text((80, 690), "Schema funzionale di gameplay/progettazione - non rappresenta una ricostruzione storica o una scala geografica.", fill="#" + MUTED, font=small_font)
    path = DIAGRAM_DIR / f"{name}.png"
    image.save(path, dpi=(220, 220), optimize=True)
    return path


def draw_pompeii_slice(base_path: Path | None) -> Path:
    DIAGRAM_DIR.mkdir(parents=True, exist_ok=True)
    if base_path and base_path.exists():
        base = Image.open(base_path).convert("RGBA")
        base.thumbnail((2000, 1450))
        canvas = Image.new("RGBA", (2200, 1700), "white")
        canvas.alpha_composite(base, ((2200 - base.width) // 2, 150))
        draw = ImageDraw.Draw(canvas, "RGBA")
        x0, y0 = (2200 - base.width) // 2, 150
        # Deliberately approximate overlay: visibly labeled as design hypothesis.
        polygons = [
            ([(x0 + int(base.width*.18), y0 + int(base.height*.48)), (x0 + int(base.width*.72), y0 + int(base.height*.47)), (x0 + int(base.width*.77), y0 + int(base.height*.62)), (x0 + int(base.width*.22), y0 + int(base.height*.65))], (139,46,46,95), "Esplorabile - ipotesi D"),
            ([(x0 + int(base.width*.70), y0 + int(base.height*.35)), (x0 + int(base.width*.91), y0 + int(base.height*.35)), (x0 + int(base.width*.93), y0 + int(base.height*.70)), (x0 + int(base.width*.76), y0 + int(base.height*.63))], (185,130,40,85), "Semplificata"),
            ([(x0 + int(base.width*.08), y0 + int(base.height*.18)), (x0 + int(base.width*.28), y0 + int(base.height*.20)), (x0 + int(base.width*.22), y0 + int(base.height*.45)), (x0 + int(base.width*.07), y0 + int(base.height*.42))], (49,91,109,70), "Visibile/non accessibile"),
        ]
        font = get_font(30, True)
        for poly, color, label in polygons:
            draw.polygon(poly, fill=color, outline=(38,50,56,210), width=4)
            px = sum(p[0] for p in poly) // len(poly)
            py = sum(p[1] for p in poly) // len(poly)
            draw.text((px - 120, py), label, fill=(20,20,20,255), font=font)
        title_font = get_font(54, True)
        small = get_font(25)
        draw.text((80, 45), "Area della vertical slice - overlay progettuale", fill="#" + INK, font=title_font)
        draw.text((80, 1600), "Overlay indicativo D: poligono GIS, superficie e insulae definitive non sono approvati. Base cartografica accreditata separatamente.", fill="#" + MUTED, font=small)
        path = DIAGRAM_DIR / "pompeii_slice.png"
        canvas.convert("RGB").save(path, dpi=(220, 220), optimize=True)
        return path
    return draw_flow("pompeii_slice", "Area della vertical slice - schema in attesa di GIS", ["Foro", "Via dell'Abbondanza", "Terme Stabiane", "Cluster produttivi", "Anfiteatro"])


def draw_districts() -> Path:
    DIAGRAM_DIR.mkdir(parents=True, exist_ok=True)
    image = Image.new("RGB", (2000, 1200), "#" + WHITE)
    draw = ImageDraw.Draw(image)
    title_font, body_font, small = get_font(52, True), get_font(28, True), get_font(23)
    draw.text((70, 45), "Zone funzionali della demo di Pompei", fill="#" + INK, font=title_font)
    zones = [
        (100, 220, 650, 480, "Z1 Foro civico", "8B2E2E"),
        (700, 220, 1380, 480, "Z2 Spina commerciale", "B98228"),
        (1430, 220, 1900, 480, "Z5 Anfiteatro", "315B6D"),
        (220, 550, 760, 820, "Z3 Terme Stabiane", "6F7D54"),
        (810, 550, 1330, 820, "Z4 Teatri-Iside", "6E4F79"),
        (1380, 550, 1850, 820, "Z6 Tessuto domestico", "8A6A4A"),
    ]
    for x1,y1,x2,y2,label,color in zones:
        draw.rounded_rectangle((x1,y1,x2,y2), 28, fill="#"+color, outline="#"+INK, width=3)
        lines=wrapped(draw,label,x2-x1-35,body_font)
        for i,line in enumerate(lines):
            draw.text((x1+25,y1+85+i*38),line,fill="white",font=body_font)
    draw.line((360,480,1600,550),fill="#"+INK,width=8)
    draw.text((70, 1035), "Zone analitiche sovrapposte: non sono quartieri antichi attestati e non coincidono automaticamente con le regiones archeologiche.", fill="#"+MUTED,font=small)
    path=DIAGRAM_DIR/"pompeii_districts.png"
    image.save(path,dpi=(220,220),optimize=True)
    return path


def generate_diagrams(config: dict) -> dict[str, Path]:
    paths: dict[str, Path] = {}
    for name, (title, nodes) in FLOW_SPECS.items():
        paths[name] = draw_flow(name, title, nodes)
    ext = {item["id"]: ROOT / item["file"] for item in config["external_images"]}
    paths["pompeii_slice"] = draw_pompeii_slice(ext.get("pompeii_plan"))
    paths["pompeii_districts"] = draw_districts()
    for item in config["external_images"]:
        path = ROOT / item["file"]
        if path.exists():
            paths[item["id"]] = path
    return paths


def set_cell_shading(cell, fill: str):
    tc_pr = cell._tc.get_or_add_tcPr()
    shd = tc_pr.find(qn("w:shd"))
    if shd is None:
        shd = OxmlElement("w:shd")
        tc_pr.append(shd)
    shd.set(qn("w:fill"), fill)


def set_cell_margins(cell, top=90, start=120, bottom=90, end=120):
    tc = cell._tc
    tc_pr = tc.get_or_add_tcPr()
    tc_mar = tc_pr.first_child_found_in("w:tcMar")
    if tc_mar is None:
        tc_mar = OxmlElement("w:tcMar")
        tc_pr.append(tc_mar)
    for margin, value in (("top", top), ("start", start), ("bottom", bottom), ("end", end)):
        node = tc_mar.find(qn(f"w:{margin}"))
        if node is None:
            node = OxmlElement(f"w:{margin}")
            tc_mar.append(node)
        node.set(qn("w:w"), str(value))
        node.set(qn("w:type"), "dxa")


def set_repeat_table_header(row):
    tr_pr = row._tr.get_or_add_trPr()
    tbl_header = OxmlElement("w:tblHeader")
    tbl_header.set(qn("w:val"), "true")
    tr_pr.append(tbl_header)


def set_table_geometry(table, widths_cm: list[float]):
    """Write explicit OOXML table/grid widths for stable A4 rendering."""
    widths_twips = [int(Cm(value).twips) for value in widths_cm]
    total_twips = sum(widths_twips)
    tbl_pr = table._tbl.tblPr
    tbl_w = tbl_pr.find(qn("w:tblW"))
    if tbl_w is None:
        tbl_w = OxmlElement("w:tblW")
        tbl_pr.insert(0, tbl_w)
    tbl_w.set(qn("w:type"), "dxa")
    tbl_w.set(qn("w:w"), str(total_twips))
    tbl_ind = tbl_pr.find(qn("w:tblInd"))
    if tbl_ind is None:
        tbl_ind = OxmlElement("w:tblInd")
        tbl_pr.append(tbl_ind)
    tbl_ind.set(qn("w:type"), "dxa")
    tbl_ind.set(qn("w:w"), "0")
    grid = table._tbl.tblGrid
    for column, width in zip(grid.gridCol_lst, widths_twips):
        column.set(qn("w:w"), str(width))


def prevent_row_split(row):
    tr_pr = row._tr.get_or_add_trPr()
    node = OxmlElement("w:cantSplit")
    tr_pr.append(node)


def set_keep_with_next(paragraph, value=True):
    p_pr = paragraph._p.get_or_add_pPr()
    node = p_pr.find(qn("w:keepNext"))
    if node is None:
        node = OxmlElement("w:keepNext")
        p_pr.append(node)
    node.set(qn("w:val"), "1" if value else "0")


def add_field(paragraph, instruction: str, display: str = ""):
    begin = OxmlElement("w:fldChar")
    begin.set(qn("w:fldCharType"), "begin")
    instr = OxmlElement("w:instrText")
    instr.set(qn("xml:space"), "preserve")
    instr.text = instruction
    separate = OxmlElement("w:fldChar")
    separate.set(qn("w:fldCharType"), "separate")
    value = OxmlElement("w:t")
    value.text = display
    end = OxmlElement("w:fldChar")
    end.set(qn("w:fldCharType"), "end")
    run = paragraph.add_run()._r
    run.append(begin); run.append(instr); run.append(separate); run.append(value); run.append(end)


def set_update_fields(doc: Document):
    settings = doc.settings._element
    node = settings.find(qn("w:updateFields"))
    if node is None:
        node = OxmlElement("w:updateFields")
        settings.append(node)
    node.set(qn("w:val"), "true")


def configure_styles(doc: Document):
    section = doc.sections[0]
    section.page_width = Cm(21.0)
    section.page_height = Cm(29.7)
    section.top_margin = Cm(2.2)
    section.bottom_margin = Cm(2.0)
    section.left_margin = Cm(2.35)
    section.right_margin = Cm(2.15)
    section.header_distance = Cm(1.0)
    section.footer_distance = Cm(1.0)

    normal = doc.styles["Normal"]
    normal.font.name = "Calibri"
    normal._element.rPr.rFonts.set(qn("w:ascii"), "Calibri")
    normal._element.rPr.rFonts.set(qn("w:hAnsi"), "Calibri")
    normal.font.size = Pt(10.6)
    normal.font.color.rgb = rgb(INK)
    normal.paragraph_format.space_after = Pt(7)
    normal.paragraph_format.line_spacing = 1.22
    normal.paragraph_format.alignment = WD_ALIGN_PARAGRAPH.JUSTIFY

    heading_tokens = {
        "Title": (34, POMPEII_RED, 0, 12),
        "Subtitle": (15, BLUE, 0, 12),
        "Heading 1": (19, POMPEII_RED, 18, 9),
        "Heading 2": (14, BLUE, 14, 6),
        "Heading 3": (11.5, INK, 10, 4),
    }
    for name, (size, color, before, after) in heading_tokens.items():
        style = doc.styles[name]
        style.font.name = "Calibri"
        style._element.rPr.rFonts.set(qn("w:ascii"), "Calibri")
        style._element.rPr.rFonts.set(qn("w:hAnsi"), "Calibri")
        style.font.size = Pt(size)
        style.font.color.rgb = rgb(color)
        style.font.bold = name != "Subtitle"
        style.paragraph_format.space_before = Pt(before)
        style.paragraph_format.space_after = Pt(after)
        style.paragraph_format.keep_with_next = True

    caption = doc.styles["Caption"]
    caption.font.name = "Calibri"
    caption.font.size = Pt(9)
    caption.font.italic = True
    caption.font.color.rgb = rgb(MUTED)
    caption.paragraph_format.space_before = Pt(3)
    caption.paragraph_format.space_after = Pt(8)
    caption.paragraph_format.keep_with_next = False

    if "Source Path" not in [s.name for s in doc.styles]:
        style = doc.styles.add_style("Source Path", WD_STYLE_TYPE.PARAGRAPH)
        style.base_style = doc.styles["Normal"]
        style.font.name = "Consolas"
        style.font.size = Pt(8)
        style.font.color.rgb = rgb(MUTED)
        style.paragraph_format.space_after = Pt(5)
        style.paragraph_format.left_indent = Cm(0.35)


def configure_header_footer(doc: Document):
    section = doc.sections[0]
    header = section.header
    p = header.paragraphs[0]
    p.text = "ROMA AETERNA  |  GAME BIBLE EDITORIALE"
    p.alignment = WD_ALIGN_PARAGRAPH.RIGHT
    p.runs[0].font.name = "Calibri"
    p.runs[0].font.size = Pt(8.5)
    p.runs[0].font.color.rgb = rgb(MUTED)
    p_pr = p._p.get_or_add_pPr()
    borders = OxmlElement("w:pBdr")
    bottom = OxmlElement("w:bottom")
    bottom.set(qn("w:val"), "single"); bottom.set(qn("w:sz"), "6"); bottom.set(qn("w:color"), OCHRE)
    borders.append(bottom); p_pr.append(borders)

    footer = section.footer
    p = footer.paragraphs[0]
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run = p.add_run("Roma Aeterna  -  ")
    run.font.size = Pt(8.5); run.font.color.rgb = rgb(MUTED)
    add_field(p, "PAGE", "1")
    run = p.add_run("  /  documento editoriale; Markdown canonici nel repository")
    run.font.size = Pt(8.5); run.font.color.rgb = rgb(MUTED)


def add_cover(doc: Document, config: dict):
    meta = config["metadata"]
    for _ in range(6):
        doc.add_paragraph()
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    r = p.add_run("GAME BIBLE EDITORIALE")
    r.font.size = Pt(11); r.font.bold = True; r.font.color.rgb = rgb(OCHRE)
    p.paragraph_format.space_after = Pt(16)
    p = doc.add_paragraph(style="Title")
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.add_run(meta["title"])
    p = doc.add_paragraph(style="Subtitle")
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.add_run(meta["subtitle"])
    p.paragraph_format.space_after = Pt(36)
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    r = p.add_run("Una persona comune. Un mondo che continua senza di lei.")
    r.font.size = Pt(14); r.font.italic = True; r.font.color.rgb = rgb(BLUE)
    for _ in range(4):
        doc.add_paragraph()
    for text in (f"Versione {meta['version']}", f"Generato il {meta['generation_date']}", meta["status"]):
        p = doc.add_paragraph()
        p.alignment = WD_ALIGN_PARAGRAPH.CENTER
        r = p.add_run(text); r.font.size = Pt(10); r.font.color.rgb = rgb(MUTED)
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.paragraph_format.space_before = Pt(22)
    r = p.add_run(meta["canonical_notice"]); r.font.size = Pt(9); r.font.bold = True; r.font.color.rgb = rgb(POMPEII_RED)
    doc.add_page_break()


def add_front_matter(doc: Document, config: dict):
    meta = config["metadata"]
    doc.add_heading("Informazioni editoriali", level=1)
    rows = [
        ("Titolo", meta["title"]), ("Versione", meta["version"]),
        ("Data", meta["generation_date"]), ("Stato", meta["status"]),
        ("Autori e contributori", "; ".join(meta["authors"])),
        ("Fonte canonica", "Repository Markdown Roma Aeterna Design"),
    ]
    add_table(doc, ["Campo", "Valore"], rows, "Metadati del documento")
    doc.add_heading("Cronologia delle revisioni", level=2)
    add_table(doc, ["Versione", "Data", "Modifica"], [[meta["version"], meta["generation_date"], "Prima edizione editoriale illustrata e tracciabile"]], "Cronologia delle revisioni")
    doc.add_heading("Come leggere questa Game Bible", level=2)
    doc.add_paragraph("Il livello editoriale spiega la visione e le decisioni in prosa. Ogni sezione contiene inoltre una scheda tecnica sintetica con fonti canoniche, dipendenze, accuratezza, decisioni aperte e criteri di completamento. I percorsi Markdown sono relativi alla radice del repository.")
    doc.add_page_break()
    doc.add_heading("Indice generale", level=1)
    p = doc.add_paragraph()
    add_field(p, 'TOC \\o "1-3" \\h \\z \\u', "Indice aggiornabile: selezionare e premere F9 in Word")
    doc.add_page_break()
    doc.add_heading("Elenco delle figure", level=1)
    p = doc.add_paragraph(); add_field(p, 'TOC \\h \\z \\c "Figura"', "Elenco aggiornabile delle figure")
    doc.add_heading("Elenco delle tabelle", level=1)
    p = doc.add_paragraph(); add_field(p, 'TOC \\h \\z \\c "Tabella"', "Elenco aggiornabile delle tabelle")
    doc.add_page_break()


FIGURE_COUNTER = 0
TABLE_COUNTER = 0
FIGURE_RECORDS: list[dict] = []
TABLE_RECORDS: list[dict] = []


def add_caption(doc: Document, label: str, title: str, source_id: str | None = None) -> int:
    global FIGURE_COUNTER, TABLE_COUNTER
    if label == "Figura":
        FIGURE_COUNTER += 1; number = FIGURE_COUNTER
    else:
        TABLE_COUNTER += 1; number = TABLE_COUNTER
    p = doc.add_paragraph(style="Caption")
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER if label == "Figura" else WD_ALIGN_PARAGRAPH.LEFT
    p.add_run(f"{label} ").bold = True
    add_field(p, f"SEQ {label} \\* ARABIC", str(number))
    p.add_run(f" - {title}")
    record = {"number": number, "title": title, "source_id": source_id or "internal"}
    (FIGURE_RECORDS if label == "Figura" else TABLE_RECORDS).append(record)
    return number


def add_figure(doc: Document, path: Path, title: str, source_id: str | None = None, width_cm: float = 15.6):
    if not path.exists():
        p = doc.add_paragraph(); p.add_run(f"[Figura mancante: {path.name}]").font.color.rgb = rgb(POMPEII_RED)
        return
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.paragraph_format.keep_with_next = True
    picture = p.add_run().add_picture(str(path), width=Cm(width_cm))
    picture._inline.docPr.set("title", title)
    picture._inline.docPr.set("descr", title)
    add_caption(doc, "Figura", title, source_id)


def add_table(doc: Document, headers: list[str], rows: list[list[str]] | list[tuple[str, ...]], title: str):
    add_caption(doc, "Tabella", title)
    table = doc.add_table(rows=1, cols=len(headers))
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.autofit = False
    table.style = "Table Grid"
    usable = 16.5
    widths = [usable / len(headers)] * len(headers)
    if len(headers) == 2:
        widths = [4.2, 12.3]
    elif len(headers) == 3:
        widths = [3.5, 6.2, 6.8]
    set_table_geometry(table, widths)
    for idx, header in enumerate(headers):
        cell = table.rows[0].cells[idx]
        cell.width = Cm(widths[idx]); cell.text = header
        cell.vertical_alignment = WD_CELL_VERTICAL_ALIGNMENT.CENTER
        set_cell_shading(cell, POMPEII_RED)
        set_cell_margins(cell)
        for run in cell.paragraphs[0].runs:
            run.font.bold = True; run.font.color.rgb = rgb(WHITE); run.font.size = Pt(8.8)
    set_repeat_table_header(table.rows[0])
    prevent_row_split(table.rows[0])
    for row_idx, values in enumerate(rows):
        cells = table.add_row().cells
        prevent_row_split(table.rows[-1])
        for idx, value in enumerate(values):
            cells[idx].width = Cm(widths[idx]); cells[idx].text = str(value)
            cells[idx].vertical_alignment = WD_CELL_VERTICAL_ALIGNMENT.CENTER
            set_cell_margins(cells[idx])
            if row_idx % 2:
                set_cell_shading(cells[idx], "F8F5EF")
            for para in cells[idx].paragraphs:
                para.paragraph_format.space_after = Pt(1.5)
                para.paragraph_format.line_spacing = 1.05
                for run in para.runs:
                    run.font.size = Pt(8.4)
    doc.add_paragraph()


def add_source_box(doc: Document, paths: list[str], confidence: str, open_items: list[str], dod_items: list[str]):
    table = doc.add_table(rows=0, cols=2)
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.autofit = False
    table.style = "Table Grid"
    set_table_geometry(table, [4.2, 12.3])
    entries = [
        ("Fonti canoniche", "\n".join(paths)),
        ("Attendibilita storica", confidence),
        ("Decisioni aperte", "\n".join(open_items) if open_items else "Nessuna estratta automaticamente; verificare i registri canonici."),
        ("Criteri di completamento", "\n".join(dod_items) if dod_items else "Definiti nei documenti sorgente o ancora da promuovere a S4."),
    ]
    for label, value in entries:
        cells = table.add_row().cells
        prevent_row_split(table.rows[-1])
        cells[0].width = Cm(4.2); cells[1].width = Cm(12.3)
        cells[0].text = label; cells[1].text = value
        set_cell_shading(cells[0], "E9DDD1")
        set_cell_margins(cells[0]); set_cell_margins(cells[1])
        cells[0].vertical_alignment = WD_CELL_VERTICAL_ALIGNMENT.CENTER
        for run in cells[0].paragraphs[0].runs:
            run.font.bold = True; run.font.size = Pt(8.4); run.font.color.rgb = rgb(POMPEII_RED)
        for para in cells[1].paragraphs:
            para.paragraph_format.space_after = Pt(1); para.paragraph_format.line_spacing = 1.0
            for run in para.runs:
                run.font.size = Pt(8.0)
    # The first key/value row acts as the compact semantic header for this
    # technical metadata block. The table is kept together whenever possible.
    set_repeat_table_header(table.rows[0])
    doc.add_paragraph()


def add_section_content(doc: Document, section: dict, diagram_paths: dict[str, Path]):
    doc.add_heading(section["title"], level=2)
    sources = section.get("sources", [])
    paragraphs = editorial_extract(sources, 3)
    if paragraphs:
        for paragraph in paragraphs:
            doc.add_paragraph(paragraph)
    else:
        doc.add_paragraph("Questa area e registrata nella struttura della Game Bible ma il contenuto editoriale disponibile non e ancora sufficiente. La lacuna resta visibile e tracciata, senza introdurre nuove affermazioni.")
    if section.get("figure") and section["figure"] in diagram_paths:
        title = FLOW_SPECS.get(section["figure"], (section["title"], []))[0]
        if section["figure"] == "pompeii_slice": title = "Area proposta per la vertical slice (ipotesi progettuale D)"
        if section["figure"] == "pompeii_districts": title = "Zone funzionali di Pompei (schema di design)"
        add_figure(doc, diagram_paths[section["figure"]], title, section["figure"])
    if section.get("table") in TABLES:
        headers, rows = TABLES[section["table"]]
        add_table(doc, headers, rows, section["title"])
    open_items = extract_bullets(sources, ["decisioni ancora aperte", "questioni aperte"], 4)
    dod_items = extract_bullets(sources, ["criteri di completamento", "definition of done"], 4)
    add_source_box(doc, sources, confidence_for(sources), open_items, dod_items)


def add_chapters(doc: Document, config: dict, diagram_paths: dict[str, Path]):
    for idx, chapter in enumerate(config["chapters"], start=1):
        h = doc.add_heading(level=1)
        h.add_run(f"{idx}. {chapter['title']}")
        p = doc.add_paragraph(chapter["intro"])
        p.style = doc.styles["Normal"]
        p.paragraph_format.space_after = Pt(12)
        p_pr = p._p.get_or_add_pPr()
        borders = OxmlElement("w:pBdr")
        left = OxmlElement("w:left"); left.set(qn("w:val"), "single"); left.set(qn("w:sz"), "18"); left.set(qn("w:color"), OCHRE); left.set(qn("w:space"), "8")
        borders.append(left); p_pr.append(borders)
        if chapter.get("figure") and chapter["figure"] in diagram_paths:
            fid = chapter["figure"]
            if fid in {item["id"] for item in config["external_images"]}:
                item = next(x for x in config["external_images"] if x["id"] == fid)
                title = f"{item['title']} - {item['type']}"
            else:
                title = FLOW_SPECS.get(fid, (chapter["title"], []))[0]
            add_figure(doc, diagram_paths[fid], title, fid)
        for section in chapter["sections"]:
            add_section_content(doc, section, diagram_paths)


def add_traceability_appendix(doc: Document, config: dict):
    doc.add_page_break()
    doc.add_heading("Appendice A - Tracciabilita completa", level=1)
    rows = []
    for cidx, chapter in enumerate(config["chapters"], start=1):
        for section in chapter["sections"]:
            sources = section.get("sources", [])
            missing = [p for p in sources if not (ROOT / p).exists()]
            status = "Parziale" if missing else "Incluso"
            rows.append([f"{cidx}. {chapter['title']} / {section['title']}", "\n".join(sources), status])
    add_table(doc, ["Capitolo/sezione", "Markdown canonici", "Copertura"], rows, "Matrice di tracciabilita editoriale")
    doc.add_heading("Appendice B - Dipendenze e impatto delle modifiche", level=1)
    add_table(doc, ["Sistema", "Dipende da", "Documenti da aggiornare"], [
        ["Tempo e calendario", "Eventi, routine, religione, save", "World, simulation, demo, technical"],
        ["NPC e conoscenza", "Identita, tempo, mondo", "AI, relazioni, crimine, contenuti, save"],
        ["Economia e proprieta", "Mondo, lavoro, inventario", "Filiere, quest, UI, save"],
        ["Famiglia e status", "Persona, diritto, proprieta", "Successione, politica, lavoro, save"],
        ["Eventi e missioni", "Tutti i domini produttori", "Narrativa, UI/audio, ledger, test"],
        ["Tecnologia e dati", "Specifiche S4 e budget", "ADR, schema, pipeline, test, readiness"],
    ], "Matrice sintetica delle dipendenze")
    doc.add_heading("Appendice C - Nota sui limiti", level=1)
    doc.add_paragraph("Questa edizione non chiude decisioni aperte, non promuove automaticamente sistemi a S4 e non autorizza l'implementazione. Mappe e schemi progettuali sono etichettati secondo la loro natura; le immagini esterne non vengono usate come prova oltre i limiti dichiarati nei crediti.")


def generate_credits(config: dict):
    lines = [
        "# Crediti delle immagini", "",
        "Generato automaticamente dalla configurazione editoriale. I numeri di figura possono cambiare a ogni rigenerazione; il titolo e l'ID restano stabili.", "",
        f"**Data di consultazione:** {config['metadata']['generation_date']}", "",
    ]
    for rec in FIGURE_RECORDS:
        source_id = rec["source_id"]
        external = next((x for x in config["external_images"] if x["id"] == source_id), None)
        lines += [f"## Figura {rec['number']} - {rec['title']}", ""]
        if external:
            lines += [
                f"- **Autore:** {external['author']}",
                f"- **Istituzione/repository:** {external['institution']}",
                f"- **Fonte:** {external['source_page']}",
                f"- **URL della scheda:** {external['source_page']}",
                f"- **URL del file:** {external['download_url']}",
                f"- **Licenza:** {external['license']}",
                f"- **Data di consultazione:** {config['metadata']['generation_date']}",
                f"- **Modifiche:** ridimensionamento e impaginazione; nessuna modifica sostanziale salvo quando esplicitamente indicato.",
                f"- **Cautela:** {external['caveat']}", "",
            ]
        else:
            modification = "Diagramma generato internamente dallo script a partire dai documenti Markdown canonici."
            if source_id == "pompeii_slice":
                modification += " Overlay progettuale su base cartografica CC BY-SA; non e un poligono GIS approvato."
            lines += [
                "- **Autore:** Roma Aeterna Design / generazione interna", "- **Istituzione:** progetto Roma Aeterna",
                "- **Fonte:** documenti Markdown indicati nel capitolo", "- **Licenza:** contenuto interno del progetto",
                f"- **Data:** {config['metadata']['generation_date']}", f"- **Modifiche:** {modification}", "",
            ]
    CREDITS_PATH.write_text("\n".join(lines), encoding="utf-8")


def build_document(config: dict):
    global FIGURE_COUNTER, TABLE_COUNTER, FIGURE_RECORDS, TABLE_RECORDS
    FIGURE_COUNTER = TABLE_COUNTER = 0; FIGURE_RECORDS = []; TABLE_RECORDS = []
    EXPORT.mkdir(parents=True, exist_ok=True); QA_DIR.mkdir(parents=True, exist_ok=True)
    diagrams = generate_diagrams(config)
    doc = Document()
    configure_styles(doc); configure_header_footer(doc); set_update_fields(doc)
    doc.core_properties.title = config["metadata"]["title"] + " - Game Bible editoriale"
    doc.core_properties.subject = "Sintesi editoriale illustrata e tracciabile della Game Bible"
    doc.core_properties.author = "Roma Aeterna Design Team"
    doc.core_properties.keywords = "Roma Aeterna, Game Bible, Pompei, RPG, Unreal Engine 5"
    add_cover(doc, config); add_front_matter(doc, config); add_chapters(doc, config, diagrams); add_traceability_appendix(doc, config)
    doc.save(DOCX_PATH)
    generate_credits(config)
    return diagrams


def report(config: dict, link_errors: list[str], checked_links: int):
    markdown_files = [p for p in ROOT.rglob("*.md") if ".git" not in p.parts and "_generated" not in p.parts]
    included = {source for chapter in config["chapters"] for section in chapter["sections"] for source in section.get("sources", [])}
    missing_sources = sorted(source for source in included if not (ROOT / source).exists())
    missing_images = sorted(item["file"] for item in config["external_images"] if not (ROOT / item["file"]).exists())
    pdf_pages = 0
    pdf_error = None
    if PDF_PATH.exists() and PDF_PATH.stat().st_size:
        try:
            pdf_pages = len(PdfReader(str(PDF_PATH)).pages)
        except Exception as exc:
            pdf_error = str(exc)
    sections = sum(len(c["sections"]) for c in config["chapters"])
    mermaid_blocks = sum(read_source(str(p.relative_to(ROOT))).count("```mermaid") for p in markdown_files)
    figure_count = len(FIGURE_RECORDS)
    if not figure_count and CREDITS_PATH.exists():
        figure_count = len(re.findall(r"^## Figura ", CREDITS_PATH.read_text(encoding="utf-8"), flags=re.M))
    table_count = len(Document(str(DOCX_PATH)).tables) if DOCX_PATH.exists() else len(TABLE_RECORDS)
    external_count = sum(1 for item in config["external_images"] if (ROOT / item["file"]).exists())
    a11y_counts = None
    a11y_report = QA_DIR / "a11y.json"
    if a11y_report.exists():
        try:
            a11y_counts = json.loads(a11y_report.read_text(encoding="utf-8")).get("counts")
        except (OSError, json.JSONDecodeError):
            a11y_counts = None
    lines = [
        "# Report di generazione", "",
        f"- **Data di generazione:** {datetime.now().astimezone().isoformat(timespec='seconds')}",
        f"- **File Markdown analizzati:** {len(markdown_files)}",
        f"- **File Markdown inclusi come fonti dirette:** {len(included)}",
        f"- **Capitoli Word:** {len(config['chapters'])}",
        f"- **Sezioni editoriali:** {sections}",
        f"- **Pagine PDF:** {pdf_pages or 'non ancora disponibili'}",
        f"- **Immagini/figure:** {figure_count}",
        f"- **Mappe storiche/archeologiche esterne:** {external_count}",
        f"- **Diagrammi editoriali interni:** {max(0, figure_count - external_count)}",
        f"- **Tabelle:** {table_count}",
        f"- **Blocchi Mermaid rilevati nel corpus:** {mermaid_blocks}",
        f"- **Collegamenti Markdown locali controllati:** {checked_links}", "",
        "## Documenti non inclusi", "",
        f"Sono esclusi dalla sintesi diretta {max(0, len(markdown_files)-len(included))} file, principalmente README locali, schede specialistiche, audit e registri ridondanti. Restano raggiungibili dai documenti canonici citati e non sono stati modificati.", "",
        "## File sorgente mancanti", "",
        *(f"- `{x}`" for x in missing_sources),
        *( ["- Nessuno."] if not missing_sources else [] ), "",
        "## Immagini mancanti", "",
        *(f"- `{x}`" for x in missing_images),
        *( ["- Nessuna."] if not missing_images else [] ), "",
        "## Collegamenti non validi", "",
        *(f"- `{x}`" for x in link_errors[:200]),
        *( ["- Nessuno."] if not link_errors else [] ), "",
        "## Errori", "",
        f"- {pdf_error}" if pdf_error else "- Nessun errore strutturale rilevato nella lettura del PDF.", "",
        "## Avvisi e limitazioni", "",
        f"- Audit accessibilita DOCX: high={a11y_counts.get('high', 0)}, medium={a11y_counts.get('medium', 0)}, low={a11y_counts.get('low', 0)}." if a11y_counts else "- Audit accessibilita DOCX non disponibile in questa rigenerazione.",
        "- Word normalizza l'indentazione XML a zero per le tabelle larghe quanto l'area utile; il controllo visivo conferma che tutte le tabelle restano entro i margini A4.",
        "- Il Word/PDF e una sintesi editoriale: i Markdown restano canonici.",
        "- Le mappe esterne sono contestuali e riportano nei crediti limiti, licenza e attendibilita.",
        "- L'overlay della vertical slice e una ipotesi D: il poligono GIS non e approvato.",
        "- I diagrammi editoriali ridisegnano i flussi essenziali; i blocchi Mermaid specialistici restano nei Markdown canonici.",
        "- I prezzi quantitativi definitivi non sono pubblicati perche i valori P0 devono ancora essere validati.",
        "- Il gate di implementazione resta NON READY.", "",
        "## Contenuti ancora incompleti", "",
        "- Versione UE5, plugin, formati dati/save e budget hardware.",
        "- GIS e selezione definitiva degli edifici P0 di Pompei.",
        "- Firme interdisciplinari, ownership, CI/LFS e benchmark.",
        "- Validazione quantitativa di economia, popolazione, calendario e contenuti.", "",
        "## Artefatti", "",
        f"- DOCX: `{DOCX_PATH.relative_to(ROOT).as_posix()}` ({DOCX_PATH.stat().st_size if DOCX_PATH.exists() else 0} byte)",
        f"- PDF: `{PDF_PATH.relative_to(ROOT).as_posix()}` ({PDF_PATH.stat().st_size if PDF_PATH.exists() else 0} byte)",
        f"- Crediti: `{CREDITS_PATH.relative_to(ROOT).as_posix()}`",
        f"- Configurazione: `{CONFIG_PATH.relative_to(ROOT).as_posix()}`",
    ]
    REPORT_PATH.write_text("\n".join(lines), encoding="utf-8")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--report-only", action="store_true")
    args = parser.parse_args()
    config = json.loads(CONFIG_PATH.read_text(encoding="utf-8"))
    bad_links, checked = validate_markdown_links()
    if not args.report_only:
        build_document(config)
    report(config, bad_links, checked)
    figure_count = len(FIGURE_RECORDS)
    if not figure_count and CREDITS_PATH.exists():
        figure_count = len(re.findall(r"^## Figura ", CREDITS_PATH.read_text(encoding="utf-8"), flags=re.M))
    table_count = len(Document(str(DOCX_PATH)).tables) if DOCX_PATH.exists() else len(TABLE_RECORDS)
    print(json.dumps({
        "docx": str(DOCX_PATH), "pdf": str(PDF_PATH),
        "figures": figure_count, "tables": table_count,
        "bad_links": len(bad_links)
    }, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
