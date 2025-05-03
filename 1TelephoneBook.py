'''
Consider telephone book database of N clients. 
Make use of a hash table implementation to quickly look up client‘s telephone number. 
Make use of two collision handling techniques and 
compare them using number of comparisons required to find a set of telephone numbers
'''

class node :
    def __init__(self, value) :
        self.value = value
        self.next = None

class HashingChain :
    def __init__(self) :
        self.Table = [None] * 10

    def hash_function(self, number) :
        return number%10
    
    def insert(self, number) :
        index = self.hash_function(number)
        new_node = node(number)

        if(self.Table[index] == None) :
            self.Table[index] = new_node
        else :
            temp_node = self.Table[index]

            while(temp_node.next != None) :
                temp_node = temp_node.next

            temp_node.next = new_node
        print("Inserted using Separate Chaining.")
    
    def search(self, number) :
        index = self.hash_function(number)
        temp_Node = self.Table[index]
        cmpr = 0
        while(temp_Node != None) :
            cmpr += 1
            if(temp_Node.value == number) :
                print("Telephone number is availabe in Table.")
                return cmpr
            temp_Node = temp_Node.next
        print("Telephone number not found.")
        return cmpr
    
    def Delete(self, number) :
        index = self.hash_function(number)
        temp_node = self.Table[index]
        prev_node = None

        while(temp_node != None) :
            if(temp_node.value == number) :
                if(prev_node == None) :
                    self.Table[index] = temp_node.next
                else :
                    prev_node.next = temp_node.next
                print("Deleted from Separate Chaining.")
                return
            prev_node = temp_node
            temp_node = temp_node.next

        print("Telephone number not found..")

    def display(self) :
        for i in range(10) :
            temp_node = self.Table[i]
            print(f"\na[{i}]", end="")
            while(temp_node != None) :
                print(f"->{temp_node.value}",end=" ")
                temp_node = temp_node.next
            
        
class HashingLinear :
    def __init__(self) :
        self.Table = [-1] * 10

    def hash_function(self, number) :
        return number%10

    def insert(self, number) :
        index = self.hash_function(number)
        for i in range(10) :
            probeIndex = (i + index) % 10
            if(self.Table[probeIndex] == -1) :
                self.Table[probeIndex] = number
                print("Inserted using Linear Probing.")
                return
        print("Hash Table is full... !!")
    
    def search(self, number) :
        index = self.hash_function(number)
        cmpr = 0

        for i in range(10) :
            probeIndex = (i + index) % 10
            if(self.Table[probeIndex] == number) :
                print("Found in linear probing.")
                return cmpr
            if(self.Table[probeIndex] == -1) :
                break
        print("Telephone number not found in linear Probing.")
        return cmpr

    def Delete(self, number) :
        index = self.hash_function(number)
        
        for i in range(10) :
            probeIndex = (i + index) % 10
            if(self.Table[probeIndex] == number) :
                self.Table[probeIndex] = -1
                print("Deleted using linear probing.")
                return
            
        print("Telephone number not found in linear Probing.")
    
    def display(self) :
        for i in range(10) :
            print(f"a[{i}] : ",end="")
            if(self.Table[i] == -1) :
                print(" ")
            else :
                print(f"{self.Table[i]}")
        

def main() :
    print("\n1. Separate Chaining. \n2. Linear Probing.")
    method = int(input("Choose Hashing Method : "))

    hc = HashingChain()
    hl = HashingLinear()

    while(True) :
        print("\n1. Add Telephone Number.\n2. Search Telephone Number.\n3. Delete Telephone Number.\n4. Display Table.\n5. Exit.")
        ch = int(input("Enter your choice : "))

        if(ch == 1) :
            number = int(input("\nEnter telephone number to insert : "))
            if(method == 1) :
                hc.insert(number)
            else :
                hl.insert(number)
        elif(ch == 2) :
            number = int(input("\nEnter telephone number to search : "))
            if(method == 1) :
                comparison = hc.search(number)
            else :
                comparison = hl.search(number)
            print("Comparisons made : ", comparison)
        elif(ch == 3) :
            number = int(input("\nEnter telephone number to delete : "))
            if(method == 1) : 
                hc.Delete(number)
            else :
                hl.Delete(number)
        elif(ch == 4) :
            if(method == 1) :
                hc.display()
            else :
                hl.display()
        elif(ch == 5) :
            print("\nProgram exited successfully.. :)\n")
            break
        else :
            print("\nEnter a valid option..!!\n")

main()
        
