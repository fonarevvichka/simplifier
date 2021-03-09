import sys


def find_difference(term_one, term_two):
    differences = 0
    index = -1

    for i in range(0, len(term_one)):
        if term_one[i] != term_two[i]:
            differences += 1
            index = i

    if differences == 1:
        return index
    else:
        return -1


def check_math(term_one, term_two):
    differences = 0

    for i in range(0, len(term_one)):
        if term_one[i] != '-' and term_two[i] != '-' and term_one[i] != term_two[i]:
            differences += 1

    return differences == 0


def create_truth_table(truth_values):
    truth_table = []
    if len(truth_values) == 4:
        for a in range(0, 2):
            for b in range(0, 2):
                truth_table.append(str(a % 2) + str(b % 2))
    elif len(truth_values) == 8:
        for a in range(0, 2):
            for b in range(0, 2):
                for c in range(0, 2):
                    truth_table.append(str(a % 2) + str(b % 2) + str(c % 2))
    elif len(truth_values) == 16:
        for a in range(0, 2):
            for b in range(0, 2):
                for c in range(0, 2):
                    for d in range(0, 2):
                        truth_table.append(str(a % 2) + str(b % 2) + str(c % 2) + str(d % 2))
    elif len(truth_values) == 32:
        for a in range(0, 2):
            for b in range(0, 2):
                for c in range(0, 2):
                    for d in range(0, 2):
                        for e in range(0, 2):
                            truth_table.append(str(a % 2) + str(b % 2) + str(c % 2) + str(d % 2) + str(e %2))
    elif len(truth_values) == 64:
        for a in range(0, 2):
            for b in range(0, 2):
                for c in range(0, 2):
                    for d in range(0, 2):
                        for e in range(0, 2):
                            for f in range(0, 2):
                                truth_table.append(str(a % 2) + str(b % 2) + str(c % 2) + str(d % 2) + str(e %2) + str(f % 2))

    return truth_table

def generate_min_terms(truth_values):
    truth_table = create_truth_table(truth_values)

    min_terms = []

    print(truth_table)
    print(truth_values)
    for i in range(0, len(truth_values)):
        if (truth_values[i] == '1'):
            min_terms.append(truth_table[i])
    return min_terms


def simplify_logic(min_terms):
    augmented_min_term_tuples = []
    augmented_min_terms = []
    solo_min_terms = []

    for i in range(0, len(min_terms)):
        for j in range(0, len(min_terms)):
            if (i != j):
                difference_index = find_difference(min_terms[i], min_terms[j])
                if difference_index != -1:
                    augmented_min_terms.append(min_terms[i])
                    augmented_min_terms.append(min_terms[j])

                    augmented_min_term_tuples.append((min_terms[i],
                                                      difference_index))

                    augmented_min_term_tuples.append((min_terms[j],
                                                      difference_index))
        else:
            if min_terms[i] not in augmented_min_terms:
                if min_terms[i] not in solo_min_terms:
                    solo_min_terms.append(min_terms[i])

    edited_min_terms = []
    for min_term_tuple in augmented_min_term_tuples:
        new_min_term = list(min_term_tuple[0])
        new_min_term[min_term_tuple[1]] = '-'

        edited_min_term = ''.join(new_min_term)
        if edited_min_term not in edited_min_terms:
            edited_min_terms.append(edited_min_term)

    return solo_min_terms + edited_min_terms


def mapping_exists(min_terms, reduced_min_terms):
    matches_found = 0

    for i in range(0, len(min_terms)):  # test every min term
        for k in range(0, len(reduced_min_terms)):
            if check_math(min_terms[i], reduced_min_terms[k]):
                matches_found += 1
                break
    return matches_found == len(min_terms)


def main():
    if len(sys.argv) == 2:
        truth_values = list(sys.argv[1])
        length = len(truth_values)
        while length > 1:
            if length % 2 == 0:
                length = length / 2
            else:
                print('Invalid length of truth table')
                break
                
        min_terms = generate_min_terms(truth_values)

        # # maximally reduce min-terms
        simplified_min_terms = min_terms
        for i in range(0, len(simplified_min_terms)):
            simplified_min_terms = simplify_logic(simplified_min_terms)

        options = [simplified_min_terms]
        best_option = simplified_min_terms
        # reduce min-terms with original terms
        while len(options) != 0:
            simplified_min_terms = options.pop()
            for i in range(0, len(simplified_min_terms)):  # tries removing each min term
                # removes one simplified min term
                trimmed_min_terms = simplified_min_terms[:i] + simplified_min_terms[i+1:]
                if mapping_exists(min_terms, trimmed_min_terms):  # valid reduction
                    if len(trimmed_min_terms) <= len(best_option):
                        best_option = trimmed_min_terms
                        options.append(trimmed_min_terms)

        char_mapping = {0: 'A', 1: 'B', 2: 'C', 3: 'D', 4: 'E', 5: 'F'}

        final_equation = []
        for min_term in best_option:
            pretty_min_term = []
            for bit in range(0, len(min_term)):
                if min_term[bit] == '0':
                    pretty_min_term.append('!')
                if min_term[bit] != '-':
                    pretty_min_term.append(char_mapping[bit])
            final_equation.append(''.join(pretty_min_term))

        print(' + '.join(final_equation))
    else:
        print('Invalid command line args')


if __name__ == "__main__":
    main()