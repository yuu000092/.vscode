import time

class RASP(object):
    
    def __init__(self):
        
        pass
    def __miyu__(self) ->None:
        
        print("あいちてゆ")
        
    def loop(self) ->None:
        while True:
            self.__miyu__()
            time.sleep(2)
        
if __name__ == "__main__":
    rasp = RASP()
    print("みゆのこと")
    rasp.loop()
    
    
    