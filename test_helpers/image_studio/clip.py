from PIL import Image
old_img = Image.open('movement_speed_up.webp')
im = Image.new(mode="RGBA", size=(32, 32))
# cropped = img.crop((8, 16, 72, 80))  # (left, upper, right, lower)
im.paste(old_img, (3, 0))
im.save("movement_speed_up.png", lossless=True, quality=100, method=6)
