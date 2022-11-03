from PIL import Image
img = Image.new(mode="RGBA", size=(48, 48))
small = Image.open("monster.png")
img.paste(small, (2, 8))
img.save("boar.png")
