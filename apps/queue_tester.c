#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "\n*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "\n*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}

static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42)
        queue_delete(q, data);
    else
        *a += 1;
}

void test_iterator_del()
{
    fprintf(stderr, "\n*** TEST iterator_del ***\n");
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Increment every item of the queue, delete item '42' */
    queue_iterate(q, iterator_inc);
    TEST_ASSERT(data[0] == 2);
    TEST_ASSERT(queue_length(q) == 9);
}

void test_destroy_empty(){
    fprintf(stderr, "\n*** TEST destroy_empty ***\n");
    queue_t q = queue_create();
    TEST_ASSERT(queue_destroy(q) == 0);
}

void test_delete_empty(){
    fprintf(stderr, "\n*** TEST delete_empty ***\n");
    queue_t q = queue_create();
    int data = 10;
    void *ptr = &data;
    TEST_ASSERT(queue_delete(q, ptr) == -1);
}

void test_dequeue_empty(){
    fprintf(stderr, "\n*** TEST dequeue_empty ***\n");
    queue_t q = queue_create();
    int *ptr;
    TEST_ASSERT(queue_dequeue(q, (void**) &ptr) == -1);
}

void test_delete_same(){
    fprintf(stderr, "\n*** TEST delete_same ***\n");
    queue_t q = queue_create();
    int data = 10;
    TEST_ASSERT(queue_enqueue(q, &data) == 0);
    TEST_ASSERT(queue_length(q) == 1);
    TEST_ASSERT(queue_delete(q, &data) == 0);
    TEST_ASSERT(queue_delete(q, &data) == -1);
}

void test_destroy_nonempty(){
    fprintf(stderr, "\n*** TEST destroy_nonempty ***\n");
    queue_t q = queue_create();
    int data = 1001;
    queue_enqueue(q, &data);
    TEST_ASSERT(queue_destroy(q) == -1);
}

int main(void){
    test_create();
    test_queue_simple();
    test_iterator_del();
    test_destroy_empty();
    test_delete_empty();
    test_dequeue_empty();
    test_delete_same();
    test_destroy_nonempty();
    return 0;
}