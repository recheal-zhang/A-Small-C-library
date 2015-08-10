#**一个袖珍C库**
-------
开发环境是Visual Studio 2012，开发语言C/C++。
功能函数简介：
> 实现一个CStash用于存放**任何类型**的数据

----------

程序基本思路如下：
> * initialize：设置内部变量为适当的值。完成对CStash的必要设置。
> * add：在CStash的下一个可用位置插入一个元素。首先，它检查是否有可用空间，如果没有，用后面介绍的inflate()函数扩展存储空间。
> * fetch：用指向这个数值存放点的"下标数"重新得到这个值。fetch()首先看index是否越界，如果没有，返回所希望的变量地址，地址采用index参数计算。
> * count：计数。
> * inflate：使用new为CStash得到更大的空间块。
> * cleanUp：清空。

------
##初始化操作
```C
/*********************************************************************
* @fn      initialize
*
* @brief   Initialization function for the Generic App Task.
*          This is called during initialization and should contain
*          any application specific initialization 
*
* @param   CStash* s - the CStash.
*		   size - the size should be used to initialize the CStash size.
*
* @return  none
*/
void initialize(CStash* s, int size)
{
	s->size = size;
	s->quantity = 0;
	s->next = 0;
	s->storage = 0;
}
```
##元素添加
```C
/*********************************************************************
* @fn      add
*
* @brief   add function for the Generic App Task.
*          This is called when you need to add some value into CStash.
*
* @param   CStash* s - the CStash.
*		   element - the element you want to add into CStash.
*
* @return  int
*/
int add(CStash* s, const void* element)
{
	if (s->next >= s->quantity)
	{
		inflate(s, increment);
	}
	// Copy element into storage
	// starting at next empty space
	int startBytes = s->next * s->size;
	unsigned char* e = (unsigned char*)element;
	for (int i = 0; i < s->size; i++)
	{
		s->storage[startBytes + i] = e[i];
	}
	s->next++;
	return(s->next - 1);		// Index number
}
```
## 元素获取
```C
/*********************************************************************
* @fn      fetch
*
* @brief   fetch function for the Generic App Task.
*          This is called when you need to get some point value.
*
* @param   CStash* s - the CStash.
*		   index - the size show you where the position is.
*
* @return  void*
*/
void* fetch(CStash* s, int index)
{
	// Check index boundaries:
	assert(0 <= index);
	if(index >= s->next)
		return 0;
	// Produce pointer to desired elment
	return &(s->storage[index * s->size]);			
}
```

## 计数
```C
/*********************************************************************
* @fn      count
*
* @brief   count function for the Generic App Task.
*          This is called when you want to know the CStash memory.
*
* @param   CStash* s - the CStash.	
*
* @return  int
*/
int count(CStash *s)
{
	return s->next; 
}
```

## 开辟内存空间
```C
/*********************************************************************
* @fn      inflate
*
* @brief   inflate function for the Generic App Task.
*          This is called when you need to new storage space.
*
* @param   CStash* s - the CStash.
*		   increase - the increase show you How much memory blocks to create.
*
* @return  none
*/
void inflate(CStash* s, int increase)
{
	assert(increase > 0);
	int newQuantity = s->quantity + increase;
	int newBytes = newQuantity * s->size;
	int oldBytes = s->quantity * s->size;

	unsigned char* b = new unsigned char[newBytes];			//开辟更长的内存空间

	for (int i = 0; i < oldBytes; i++)
	{
		b[i] = s->storage[i];
	}

	delete []s->storage;
	s->storage = b;
	s->quantity = newQuantity;
}
```

## 清理内存
```C
/*********************************************************************
* @fn      cleanUp
*
* @brief   cleanUp function for the Generic App Task.
*          This is called when you want to clean the CStash.
*
* @param   CStash* s - the CStash.	
*
* @return  none
*/
void cleanUp(CStash* s)
{
	if(s->storage != 0)
	{
		cout << "free storage" << endl;
		delete []s->storage;
	}
}
```








