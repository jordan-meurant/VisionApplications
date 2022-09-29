import subprocess as sub
import tkinter
from tkinter import simpledialog
import time
from PIL import ImageTk, Image

VIEW_SIZE = (350, 300)

class Gui(tkinter.Tk):

    def __init__(self):
        super().__init__()
        self.wm_title("Arthur D. & Jordan M. Application")
        self.wm_minsize(width=300, height=300)
        self.images_dict = {
            'pois' : 'petitsPois.png',
            'tools' : 'tools.png',
            'balanes' : 'balanes.png',
            'vaisseaux': 'planete.jpg'
        }
        self.result_images_dict = {
            'pois': ['poids-rouges-result.png', 'poids-bleus-result.png'],
            'tools': ['tools-result.png'],
            'balanes' : ['petites-balanes-result.png', 'grandes-balanes-result.png'],
            'vaisseaux': ['vaisseaux-result.jpg']
        }
        self.application_type = tkinter.StringVar()
        self.performance_txt = tkinter.StringVar()
        self.performance_txt.set("No performances")
        self.setup_widgets()
    
    def load_image(self):
        temp = Image.open(self.images_dict[self.application_type.get()])
        temp = temp.resize(VIEW_SIZE)
        self.origin_image = ImageTk.PhotoImage(temp)
        return self.origin_image
    
    def setup_widgets(self):
        
        self.option_label = tkinter.Label(self, text="Choose an application", font='Helvetica 15 bold')
        self.option_box=tkinter.OptionMenu(self, self.application_type, 'pois', 'balanes', 'tools', 'vaisseaux', command=self._on_option_changes)
        self.application_type.set("pois")

        self.performances_label = tkinter.Label(self, textvariable=self.performance_txt, font='Helvetica 11 bold')
        
        self.run_button = tkinter.Button(self,  text="run", command=self._start_application)
        
        self.origin_image = self.load_image()
        self.origin_image_label = tkinter.Label(self, image = self.origin_image)
        
        #contient les labels contenant les images de résultat
        self.results_images = []
        #contient l'objet Image représentant un résultat (besoin pour éviter le carbage collector)
        self.images = []

        self.option_label.grid(row=0, column=0, ipadx=20)
        self.option_box.grid(row=0, column=1, ipadx=20)
        self.performances_label.grid(row=0, column=3, ipadx=20)
        self.run_button.grid(row=0, column=2, ipadx=20)
        self.origin_image_label.grid(row=1, column=0)
    
    def _on_option_changes(self, arg):
        self.origin_image_label.grid_remove()
        self.origin_image = self.load_image()
        self.origin_image_label = tkinter.Label(self, image = self.origin_image)
        self.origin_image_label.grid(row=1, column=0)
        for res in self.results_images:
            res.grid_remove()
        self.images.clear()
        self.performance_txt.set("No performances")
    
    def _start_application(self):
        for res in self.results_images:
            res.grid_remove()
        self.images.clear()
        self.results_images.clear()
        path = "./opencv.exe"
        #appel d'opencv
        sub.check_call([path, self.application_type.get(), "no_show_native"])
        for image_path in self.result_images_dict[self.application_type.get()]:
            temp = Image.open(image_path)
            temp = temp.resize(VIEW_SIZE)
            image = ImageTk.PhotoImage(temp)
            self.images.append(image)
            label = tkinter.Label(self, image = image)
            self.results_images.append(label)
            label.grid(row=2, column=len(self.results_images)-1)
        with open("performances.txt", "rt") as file:
            self.performance_txt.set(f"Performances: {file.readline():.3}ms ")


app = Gui()
app.mainloop()
