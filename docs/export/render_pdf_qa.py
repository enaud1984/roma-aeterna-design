#!/usr/bin/env python3
"""Crea contact sheet dalle pagine PNG renderizzate del PDF per QA visiva."""

from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[2]
QA = ROOT / "docs" / "export" / "_generated" / "qa"
OUT = QA / "contacts"
OUT.mkdir(parents=True, exist_ok=True)

pages = sorted(QA.glob("page-*.png"), key=lambda p: int(p.stem.split("-")[-1]))
font_path = Path("C:/Windows/Fonts/arial.ttf")
font = ImageFont.truetype(str(font_path), 22) if font_path.exists() else ImageFont.load_default()
per_sheet, columns = 12, 3

for old in OUT.glob("contact-*.jpg"):
    old.unlink()

for start in range(0, len(pages), per_sheet):
    sheet = Image.new("RGB", (1340, 2540), "#d8d8d8")
    draw = ImageDraw.Draw(sheet)
    for offset, page in enumerate(pages[start:start + per_sheet]):
        image = Image.open(page).convert("RGB")
        image.thumbnail((420, 594))
        x = 20 + (offset % columns) * 440
        y = 20 + (offset // columns) * 630
        draw.text((x, y), f"Pagina {start + offset + 1}", fill="black", font=font)
        sheet.paste(image, (x, y + 32))
    sheet.save(OUT / f"contact-{start // per_sheet + 1:02d}.jpg", quality=88)

print(f"Contact sheet create: {(len(pages) + per_sheet - 1) // per_sheet}")
