# GCE

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/b826615311ec44e2ae35360cd6743d2d)](https://app.codacy.com/app/ssapo/GCE?utm_source=github.com&utm_medium=referral&utm_content=ssapo/GCE&utm_campaign=Badge_Grade_Dashboard)

GC공부할려고 만드는 저장소 임니다 
레퍼런스  

[언리얼 엔진 위키](https://wiki.unrealengine.com/Garbage_Collection_%26_Dynamic_Memory_Allocation)  
   
[스택오버플로 GC와 리플렉션을 C++에서 사용하는 이유?](https://stackoverflow.com/questions/33985860/ue4-object-has-reflection-why-to-use-c-then)  
  
알아볼 것들
1. C++은 언매니지드 언어임에도 왜 언리얼은 GC를 사용하는지? 
![img](https://i.imgur.com/Hiut88i.png)  

![img](https://i.imgur.com/SdQlhl1.png)  

2. 언리얼에서는 GC를 어떤식으로 사용하는지 
(Epic wiki)
  Implications of Not Using UPROPERTY()  
If you do not use UPROPERTY() you can never rely on your dynamic UObject staying in existence!  
Make sure you pay close attention to this if you are spawning UObjects or using NewObject())!  
3. 알고리즘, 장점과 단점 
4. Unity의 C# GC와 다른 점은 무엇인지? 

알아보려고 합니닷

커맨드 창에 stat MemoryPlatform 입력

![img](https://i.imgur.com/W0vInRL.png)

Engine/Source/Runtime/CoreUObject/Private/UObject  
Engine/Source/Runtime/CoreUObject/Public/UObject  
