#include "optimizer/OWL.hpp"
#include "il/OMRNode_inlines.hpp"
#include "optimizer/Optimization.hpp"
#include "optimizer/Optimization_inlines.hpp"
#include "optimizer/OptimizationManager.hpp"
#include "optimizer/Optimizations.hpp"
#include "optimizer/Optimizer.hpp"
#include "launch.h"


TR_OWL::TR_OWL(TR::OptimizationManager *manager)
   : TR::Optimization(manager)
   {   }


TR::Optimization *TR_OWL::create(TR::OptimizationManager *manager)
   {
   return new (manager->allocator()) TR_OWL(manager);
   }

static void processTree(TR::Node *root, TR::NodeChecklist &visited) {
   if (visited.contains(root))
      return;
   visited.add(root);
   for (int32_t i = 0; i < root->getNumChildren(); ++i) {
      processTree(root->getChild(i), visited);
   }
   printf("%s\n",root->getOpCode().getName());
}

int32_t TR_OWL::perform(){
   printf("Hello world!\n");

   //start jvm
   JNIEnv *java_env = launch_jvm("");

   TR::NodeChecklist visited(comp()); // visited nodes

   for (TR::TreeTop *tt = comp()->getStartTree(); tt; tt = tt->getNextTreeTop()){
      TR::Node *node = tt->getNode();
      processTree(node, visited);

   }
}

const char *
TR_OWL::optDetailString() const throw()
   {
   return "O^O OWL: ";
   }