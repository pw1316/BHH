BHH

===
Manual

1-Indroduction
└1.1 This is My Health produced by XXX,from this you can eat more balaced and get imformation about food.
└1.2 This program consists of X files or folders,including "main.c" as the operating program,"save<num>.sav" as personal imformation file...
└1.3 All the files and foders should be put in a same folder to make sure it does not make errors.

2-Operating
└2.1 In the homepage,you can use "Up" and "Down" to select whitch menu you'd like to go into,and press "Enter" to go into the highlighted menu.
└2.2 There are 5 buttons in the home page:MyInfo,MyEating,Food,Recipe and ChangeProfile.
  └2.2.1 MyInfo will show your basic imformation.
  └2.2.2
 =============================
 
TODO:
    c)	实现常用食物营养的统计与查询；
    d)	饮食记录，简单的营养是否平衡的分析；
    e)	简单食谱的输入、显示与推荐；
count : 进食餐数
energy : 卡路里
procnt : 蛋白质
通过计算平均数估算营养平衡
<p>按分档算：</p>
<p>  energy   procnt</p>
<p>    没吃    0         0</p>
<p>    素       500     19</p>
<p>    大素  790    30</p>
<p>    荤       1000    40</p>
<p>    大荤      1500   60</p>
    
    
注释：
------------------------------------------
<ul class="intros">
        <li class="active">
          <article>
            <h4>素食</h4>
            <p>这里的素食概念，是指无论做法和食材都偏清淡，极少糖分和油腻。但又不缺少营养的正餐。</p>
            <p>一餐中，肉类的含量不超过100克。且蔬菜的含量超过食物的50%，糖份少，非油炸，非保质期大于一个月的加工食品，非速食，含油少，就算是素食。</p>
            <p>另外，鸡蛋清，小碗清鸡汤，白水煮鸡胸，清水加工的金枪鱼肉，只要不超过300克，也算做素食。</p>
            <p>当日评价：一日3餐中只要有2餐是素或大素，当日的评价就为素。但如果连续6餐都是素或大素，最后一餐当日的评价直接为荤。</p>
          </article>
        </li>
        <li>
          <article>
            <h4>大素</h4>
            <p>一餐中，蔬菜的含量超过食物的70%，且有一定量的绿色蔬菜，以杂粮为主食，肉类含量为0，无食鸡蛋黄，无糖分，非油炸，无油烹饪，或使用少量橄榄油，非零食，非保质期大于1个月的加工食品。</p>
            <p>当日评价：一日3餐中只要有2餐是素或大素，当日的评价就为素。但如果连续6餐都是素或大素，最后一餐当日的评价直接为荤。</p>
          </article>
        </li>
        <li>
          <article>
            <h4>荤食</h4>
            <p>这里的荤食概念，是指味道偏辛辣，且含丰富油腻或高糖分的食物。</p>
            <p>一餐中，肉类的含量超过100克。或蔬菜的含量小于食物的50%，油炸或油多，糖份高，这一餐就算是荤食。</p>
            <p>特别注意：含有植脂末（氢化植物油），阿斯巴甜的食物，餐馆中的纯蔬菜的麻辣香锅，沙拉酱，软饮料，啤酒，大于100g的红酒，50g的白酒，保质期大于1个月的加工食品，也都算做是荤食。</p>
            <p>当日评价：一日3餐中只要有2餐是荤或大荤，当日的评价就为荤。但如果连续3餐都是荤，那么后面的3顿必须为素，否则最后一顿的当日评价直接为荤。</p>
          </article>
        </li>
        <li>
          <article>
            <h4>大荤</h4>
            <p>大荤的标准，比较常见用于“甩开腮帮子吃”的情况，如聚餐，给自己的奖励等给自己带来极大的快感的进餐。</p>
            <p>一餐中，肉类的含量超过400克，油炸，油多，有甜食和饮料，过度饮酒，都为大荤。</p>
            <p>当日评价：大荤也同样适用于3餐2素，但是大荤之后的3顿必须为素，否则最后一顿的当日评价直接为荤。</p>
          </article>
        </li>
        <li>
          <article>
            <h4>未食</h4>
            <p>空腹未进食，或吃的很少，几块饼干或一个水果，都算未食。评价相当于荤。</p>
          </article>
        </li>
      </ul>
------------------------------------------
参考值 每天（按三餐计）
成人：
    male:
        energy 2700kcal   
        procnt 80g
     female:
        2300
        70
儿童:
    N/A