import tkinter as tk
import subprocess

# Compile the C++ program at startup
compile_result = subprocess.run(["g++", "main.cpp", "-o", "main"], capture_output=True, text=True)
if compile_result.returncode != 0:
    print("Compilation failed:", compile_result.stderr)
    exit(1)

def calculate():
    expr = entry.get().strip()
    if not expr:
        output.config(text="Please enter an expression")
        return
    with open("input.txt", "w") as f:
        f.write(expr + "\n")
    result = subprocess.run(["./main"], capture_output=True, text=True)
    if result.returncode != 0:
        output.config(text="Error running calculator")
        return
    with open("output.txt", "r") as f:
        res = f.read().strip()
    output.config(text=res)

root = tk.Tk()
root.title("Calculator")
root.geometry("300x150")

tk.Label(root, text="Enter expression:").pack(pady=5)
entry = tk.Entry(root, width=30)
entry.pack(pady=5)

button = tk.Button(root, text="Calculate", command=calculate)
button.pack(pady=5)

# Result on the same line
result_frame = tk.Frame(root)
result_frame.pack(pady=5)
tk.Label(result_frame, text="Result:").pack(side=tk.LEFT)
output = tk.Label(result_frame, text="", font=("Arial", 12))
output.pack(side=tk.LEFT)

root.mainloop()
