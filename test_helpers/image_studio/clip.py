from PIL import Image
img = Image.open('elf.webp')
cropped = img.crop((8, 16, 72, 80))  # (left, upper, right, lower)
cropped.save("elf.png", lossless=True, quality=100, method=6)
