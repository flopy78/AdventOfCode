
def inverse_matrix_without_det(matrix):
    a,b = matrix[0]
    c,d = matrix[1]
    return [[d,-b],[-c,a]]

def matrix_vector_product(matrix,vector):
    x,y = vector
    a,b = matrix[0]
    c,d = matrix[1]
    return [a*x+b*y,c*x+d*y]

def det(matrix):
    a,b = matrix[0]
    c,d = matrix[1]
    return a*d-b*c

with open("input.txt") as file:
    total_tokens = 0
    for claw in file.read().split("\n\n"):
        A_repr,B_repr,prize_repr = claw.split("\n")
        A = [int(coord[2:]) for coord in A_repr.split(": ")[1].split(", ")]
        B = [int(coord[2:]) for coord in B_repr.split(": ")[1].split(", ")]
        prize = [int(coord[2:])+10000000000000 for coord in prize_repr.split(": ")[1].split(", ")]
        claw_matrix = [
            [A[0],B[0]],
            [A[1],B[1]]
        ]

        a_coeff_without_det,b_coeff_without_det = matrix_vector_product(inverse_matrix_without_det(claw_matrix),prize)
        determinant = det(claw_matrix)
        if determinant != 0:
            if a_coeff_without_det%determinant == 0 and b_coeff_without_det%determinant == 0:
                a_coeff = a_coeff_without_det//determinant
                b_coeff = b_coeff_without_det//determinant
                total_tokens += 3*a_coeff + b_coeff
    
    print(total_tokens)

