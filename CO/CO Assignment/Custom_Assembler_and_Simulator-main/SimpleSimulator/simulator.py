# import SimpleAssembler
# Shivesh Part starts 1
import Encode as en
import sys
from matplotlib import pyplot as plt
def convert(imm):
    ans=int(imm,2)
    ans=str(ans)
    return ans
def convertDecimal(imm,n):
    ans=0
    for i in range(len(imm)):
        ans+=int(imm[i])*(2**(n-i-1))
    
    return ans
def dectobin(dec):
    n=15
    str=""
    for i in range(0,16):
        if dec//(2**n)==1:
            dec=dec%(2**n)
            str+='1'
        else:
            str+='0'
        n-=1
    return str
def bintofloat(str):
    n=4
    exp=0
    for i in range(0,3):
        if str[i]=='1':
            exp+=n
        n/=2
    man=1
    for i in range(3,8):
        if str[i]=='1':
            man+=n
        n/=2
    return man*(2**exp)
# Shivesh Part ends 1
# Aditya Part Starts
class simulator:
    def __init__(self):
        self.opcode={"00000":"add","00001":"sub","00100":"ld","00101":"st","00110":"mul","00111":"div","01001":"ls","01000":"rs","01010":"xor","01011":"or","01100":"and","01101":"not","01110":"cmp","01111":"jmp","10000":"jlt","10001":"jgt","10010":"je","10011":"hlt","00010":"movim","00011":"movr"}
        self.reg={"000":"R0", "001":"R1", "010":"R2", "011":"R3", "100":"R4","101":"R5", "110":"R6","111":"FLAGS"}
        self.instructionType={"add":'A',"sub":'A',"mul":'A',"xor":'A',"or":'A',"and":'A',"addf":"A","subf":"A","movf":"B",'movim':'B',"rs":"B","ls":"B","movr":"C","div":"C","not":"C","cmp":"C","ld":"D","st":"D","jmp":"E","jlt":"E","jgt":"E","je":"E","hlt":"F"}
        self.unusedBits={'A':"00",'C':"00000","E":"000","F":"000000000"}
        self.instructions=[]
        self.regval1={"R0":0,"R1":0,"R2":0,"R3":0,"R4":0,"R5":0,"R6":0,"FLAGS":['0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0']}
        self.regval={"R0":"0000000000000000","R1":"0000000000000000","R2":"0000000000000000","R3":"0000000000000000","R4":"0000000000000000","R5":"0000000000000000","R6":"0000000000000000","FLAGS":['0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0']}
        self.pc=0
        self.getinput()
        
    def getinput(self):
        # f=open("output.txt","r")
        self.instructions=sys.stdin.readlines()
        self.instructions="".join(self.instructions)
        self.instructions=" ".join(self.instructions.split("\n"))
        self.instructions=self.instructions.split(" ")
        n=len(self.instructions)
        i=0
        while(i<n):
            if self.instructions[i][0:5]=="10110" or self.instructions[i][0:5]=="10101":
                self.instructions.append(0)
            elif self.instructions[i]=='':
                self.instructions.pop(i)
                n-=1
                i-=1
            i+=1
        for i in range(n,256):
            self.instructions.append('0000000000000000')
    def regvalue(self,register,val):    
        # if flag==True:
        #     print(val)
        #     print(register)
        if val<0:
            self.reset()
            self.regval["FLAGS"][-4]='1'
            self.regval1["FLAGS"][-4]='1'
            self.regval1[register]=0
            self.regval[register]="0000000000000000"
        elif val>2**16-1:
            self.reset()
            self.regval["FLAGS"][-4]='1'
            self.regval1["FLAGS"][-4]='1'
            self.regval1[register]=val%(2**16)
            self.regval[register]=dectobin(self.regval1[register])
        else:
            self.regval1[register]=val
            self.regval[register]=dectobin(val)
            self.reset()
    
    def regfloat(self,register,val):
        if val<1:
            # print(val)
            self.reset()
            self.regval["FLAGS"][-4]='1'
            self.regval1["FLAGS"][-4]='1'
            self.regval1[register]=0
            self.regval[register]="0000000000000000"
        elif val>=252:
            self.reset()
            self.regval["FLAGS"][-4]='1'
            self.regval1["FLAGS"][-4]='1'
            self.regval1[register]=255
            self.regval[register]="0000000011111111"
        else:
            self.reset()
            self.regval[register]="00000000"+en.ieee(str(val))
            self.regval1[register]=convertDecimal(self.regval[register],16)
        # Aditya Part Ends
        # Shivesh Part 2 starts
    def reset(self):
        self.regval["FLAGS"]=['0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0']
    def decode(self,instruction):
            decoded=[]
            i=instruction
            register=""
            insCode=""
            insCode+=self.opcode[i[0:5]]
            type=self.instructionType[insCode]
            if type=="A":
                insCode+=" "
                register+=self.reg[i[7:10]]+" "
                register+=self.reg[i[10:13]]+" "
                register+=self.reg[i[13:16]]
                insCode+=register
                decoded.append(insCode)
            elif type=="B":
                a=insCode
                insCode+=" "
                register+=self.reg[i[5:8]]+" "
                imm=i[8:16]+" "
                if a=="movf":
                    print(i[8:16])
                    imm=str(bintofloat(i[8:16]))
                    print(imm)
                else:
                    imm=convert(imm)
                register+=imm
                insCode+=register
                decoded.append(insCode)
            elif type=="C":
                insCode+=" "
                register+=self.reg[i[10:13]]+" "
                register+=self.reg[i[13:16]]+" "
                insCode+=register
                decoded.append(insCode)
            elif type=="D":
                insCode+=" "
                register+=self.reg[i[5:8]]+" "
                imm=i[8:16]
                imm=convertDecimal(imm,8)
                imm=str(imm)
                insCode+=register+imm
                decoded.append(insCode)
            elif type=="E":
                insCode+=" "
                imm=i[8:16]
                imm=convertDecimal(imm,8)
                imm=str(imm)
                insCode+=imm
                decoded.append(insCode)
            elif type=="F":
                decoded.append(insCode)
            
            return insCode.split()
        # Shivesh Part 2 ends
        # Karan Part starts
    def executengine(self):
        flag=0
        cycles=0
        cycleslist=list()
        pclist=list()
        while(flag!=1):
            isJump=False
            i=self.decode(self.instructions[self.pc])
            # print(i)
            if i[0]=="add":
                self.regvalue(i[1],self.regval1[i[2]]+self.regval1[i[3]])
            if i[0]=="sub":

                self.regvalue(i[1],self.regval1[i[2]]-self.regval1[i[3]])
            if i[0]=="movr":

                if(i[2]=="FLAGS"):
                    self.regvalue(i[1],convertDecimal("".join(self.regval[i[2]]),16))
                else:
                    self.regvalue(i[1],self.regval1[i[2]])
            elif i[0]=="movim":

                self.regvalue(i[1],int(i[2]))
            if i[0]=="ld":
                self.regvalue(i[1],convertDecimal(self.instructions[int(i[2])],16))
            if i[0]=="st":
                self.instructions[int(i[2])]=self.regval[i[1]]
                self.reset()
            if i[0]=="mul":
                self.regvalue(i[1],self.regval1[i[2]]*self.regval1[i[3]])
            if i[0]=="div":
                self.regvalue("R0",self.regval1[i[1]]//self.regval1[i[2]])
                self.regvalue("R1",self.regval1[i[1]]%self.regval1[i[2]])
            if i[0]=="rs":
                self.regval1[i[1]]=self.regval1[i[1]]>>int(i[2])
                self.regval[i[1]]=dectobin(self.regval1[i[1]])
                self.reset()
            if i[0]=="ls":
                self.regval1[i[1]]=self.regval1[i[1]]<<int(i[2])
                self.regval[i[1]]=dectobin(self.regval1[i[1]])
                self.reset()
            if i[0]=="xor":
                self.regval1[i[1]]=self.regval1[i[2]]^self.regval1[i[3]]
                self.regval[i[1]]=dectobin(self.regval1[i[1]])
                self.reset()
            elif i[0]=="or":
                self.regval1[i[1]]=self.regval1[i[2]]|self.regval1[i[3]]
                self.regval[i[1]]=dectobin(self.regval1[i[1]])
                self.reset()
            elif i[0]=="and":
                self.regval1[i[1]]=self.regval1[i[2]]&self.regval1[i[3]]
                self.regval[i[1]]=dectobin(self.regval1[i[1]])
                self.reset()
            elif i[0]=="not":
                self.regval1[i[1]]=self.regval1[i[2]]^0b1111111111111111
                self.regval[i[1]]=dectobin(self.regval1[i[1]])
                self.reset()
            elif i[0]=="cmp":
                if(self.regval1[i[1]]<self.regval1[i[2]]):
                    self.reset()
                    self.regval["FLAGS"][-3]='1'
                elif(self.regval1[i[1]]>self.regval1[i[2]]):
                    self.reset()
                    self.regval["FLAGS"][-2]='1'
                else:
                    self.reset()
                    self.regval["FLAGS"][-1]='1'
            elif i[0]=="jmp":
                isJump=True
                loc=self.pc
                self.pc=int(i[1])-1
                self.reset()
            elif i[0]=="jlt":
                isJump=True
                loc=self.pc
                if(self.regval["FLAGS"][-3]=='1'):
                   loc=self.pc
                   self.pc=int(i[1])-1
                self.reset()
            elif i[0]=="jgt":
                isJump=True
                loc=self.pc
                if(self.regval["FLAGS"][-2]=='1'):
                    self.pc=int(i[1])-1
                self.reset()
            elif i[0]=="je":
                isJump=True
                loc=self.pc
                if(self.regval["FLAGS"][-1]=='1'):
                    self.pc=int(i[1])-1
                self.reset()
            elif i[0]=="hlt":
                loc=self.pc
                self.reset()
                flag=1
            elif i[0]=="addf":
                loc=self.pc
                val1=bintofloat(self.regval[i[1]][8:16])
                val2=bintofloat(self.regval[i[2]][8:16])
                self.regfloat(i[3],val1+val2)
            elif i[0]=="subf":
                loc=self.pc
                val1=bintofloat(self.regval[i[1]][8:16])
                val2=bintofloat(self.regval[i[2]][8:16])
                self.regfloat(i[3],val1-val2)
            elif i[0]=="movf":
                loc=self.pc
                self.regfloat(i[1],float(i[2]))
            self.pc+=1
            cycles+=1
            cycleslist.append(cycles)
            registers="".join(self.regval["FLAGS"])
            if isJump==True:
                print(f"{dectobin(loc)[8:16]} {self.regval['R0']} {self.regval['R1']} {self.regval['R2']} {self.regval['R3']} {self.regval['R4']} {self.regval['R5']} {self.regval['R6']} {registers}")
                pclist.append(loc)
            else:
                print(f"{dectobin(self.pc-1)[8:16]} {self.regval['R0']} {self.regval['R1']} {self.regval['R2']} {self.regval['R3']} {self.regval['R4']} {self.regval['R5']} {self.regval['R6']} {registers}")
                pclist.append(self.pc-1)
        for i in range(0,256):
            print(self.instructions[i])
        # Karan Part ends
        plt.xlabel("Cycle Number")
        plt.ylabel("Memory Address")
        plt.scatter(cycleslist,pclist)
        plt.show()
s=simulator()
s.executengine()
