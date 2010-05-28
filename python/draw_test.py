import Image, ImageDraw

#im=Image.open("/home/dsipos/Pictures/atomicMushroomCloud.jpg")
#im.rotate(45).show()
out_file = "/tmp/load.png"
im=Image.new("RGB", (400, 400))
draw=ImageDraw.Draw(im)
width=200
row_size=12
def draw_box(label, color, center = False):
    ypos = draw_box.ypos
    xpos = 1
    if center:
        w, h = draw.textsize(label)
        xpos = (width - w) / 2
    draw.rectangle(((1, ypos), (width-2, ypos + row_size)), color)
    draw.text((xpos,ypos+1), label, fill = "#000000")
    draw_box.ypos += row_size
draw_box.ypos = 0

#draw.text((100, 100), "DUMI TEST", fill="#FFFF00")
#draw.rectangle(((50,50), (150, 150)), "#DDBBCC")
#draw.text((100, 100), "DUMI TEST", fill="#FFFF00")
draw_box(" ==== DATABASES ==== ", "#BBBBBB", center = True)
draw_box(" ==== SERVICES ==== ", "#BBBBBB", center = True)
#im.show()
#print im.histogram()
with open(out_file, 'w') as handle:
    im.save(handle, "PNG")
