'''
TDA Grafo 
'''

import random
class Grafo:
    def __init__(self, es_dirigido):
        self.vertices = {}
        self.es_dirigido = es_dirigido
        self.cant_vertices = 0
    

    def agregar_vertice(self, vertice, dato = None):
        if vertice not in self.vertices:
            self.vertices[vertice] = {}
            self.cant_vertices += 1
    
    def borrar_vertice(self, vertice):
        if vertice not in self.vertices:
            return False
        for w in self.vertices.values():
            if vertice in w:
                w.pop(vertice)
        del self.vertices[vertice]
        self.cant_vertices -= 1


    def agregar_arista(self, v1, v2, peso = None):
        if v1 not in self.vertices or v2 not in self.vertices:
            return False
        self.vertices[v1][v2] = peso
        if self.es_dirigido == False:    #Si el grafo es no dirigido, se tiene que agregar la arista de "vuelta"
            self.vertices[v2][v1] = peso
        return True


    def borrar_arista(self, v1, v2):
        if v1 not in self.vertices or v2 not in self.vertices[v1]:
            return False
        self.vertices[v1].pop(v2)
        if self.es_dirigido == False:
            self.vertices[v2].pop(v1)
        return True
        

    def adyacentes(self, vertice):
        if vertice in self.vertices:
            return self.vertices[vertice].keys()

    def obtener_vertice(self, vertice):
        if vertice in self.vertices:
            return self.vertices[vertice]
        else:
            return None
    
    def vertice_aleatorio(self):
        return random.choice(list(self.vertices.keys()))

    def vertice_pertenece(self, vertice):
        return vertice in self.vertices

    def vertices_cantidad(self):
        #o se puede hacer con un len(self.vertices)
        return self.cant_vertices
    
    def estan_conectados(self,v1,v2):
        return v2 in self.vertices[v1]
    
    def obtener_todos_vertices(self):
        return self.vertices.keys()

    def obtener_peso(self, v1, v2):
        if v1 not in self.vertices or v2 not in self.vertices:
            return False
        return self.vertices[v1][v2]

    def __iter__(self):
        return iter(self.vertices)

