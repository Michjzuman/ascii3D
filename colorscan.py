#!/usr/bin/env python3
"""Anteile weisser und grüner Pixel auf einer Skala von 0 bis 255.

Die Anteile beziehen sich nur auf die Summe dieser beiden Farben.

Aufruf: python3 colorscan.py bild.png [--tolerance 20]
Benötigt Pillow: python3 -m pip install Pillow
"""

import argparse


def tolerance_value(value):
    value = int(value)
    if not 0 <= value <= 127:
        raise argparse.ArgumentTypeError("Toleranz muss zwischen 0 und 127 liegen.")
    return value


def count_colors(image, tolerance=0):
    """Zähle RGB-Nähe zu Weiss/Grün; vollständig transparente Pixel ignorieren."""
    white = 0
    green = 0
    for red, g, blue, alpha in image.convert("RGBA").getdata():
        if alpha == 0:
            continue
        if min(red, g, blue) >= 255 - tolerance:
            white += 1
        elif red <= tolerance and g >= 255 - tolerance and blue <= tolerance:
            green += 1
    return white, green


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", help="Pfad zum Eingabebild")
    parser.add_argument(
        "--tolerance", type=tolerance_value, default=0, metavar="0-127",
        help="Maximale Abweichung pro RGB-Kanal (Standard: 0, exakte Farben).",
    )
    args = parser.parse_args()

    try:
        from PIL import Image
    except ImportError:
        parser.exit(1, "Pillow fehlt. Installieren mit: python3 -m pip install Pillow\n")

    try:
        with Image.open(args.image) as image:
            white, green = count_colors(image, args.tolerance)
    except (OSError, ValueError, Image.DecompressionBombError) as error:
        parser.exit(1, f"Bild konnte nicht gelesen werden: {error}\n")

    total = white + green
    print(f"Weisse und grüne Pixel insgesamt: {total}")
    if total == 0:
        print("Keine weissen oder grünen Pixel gefunden; Anteile nicht definiert.")
        return
    print(f"Weiss: {white / total * 255:.2f}/255 ({white} Pixel)")
    print(f"Grün:  {green / total * 255:.2f}/255 ({green} Pixel)")


if __name__ == "__main__":
    main()
