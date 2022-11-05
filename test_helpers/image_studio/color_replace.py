from PIL import Image, ImageColor


img = Image.open('out.png')
img = img.convert("RGBA")
pix_data = img.load()
c = pix_data[0, 0]
for y in range(img.size[1]):
    for x in range(img.size[0]):
        if pix_data[x, y] == c:
            pix_data[x, y] = (0, 0, 0, 0)
img.save("out1.png", "PNG", lossless=True, quality=100, method=6)