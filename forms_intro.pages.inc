<?php
/**
 * Implements hook_form().
 */
function forms_intro_form($node, &$form_state) {
  $type = node_type_get_type($node);
  $form = array();

  $form['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please enter your info.'),
    '#description' => t('If you would like to contact us.')
  );

  $form['contact']['first_name']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your name'),
            '#description'=>t('Please enter first name.')
          );
  $form['contact']['last_name']=array(
      '#type'=>'textfield',
      '#title'=>t('Enter your Last name'),
      '#description'=>t('Please enter last name.')
    );

   $form['contact']['email']=array(
      '#type'=>'textfield',
      '#title'=>t('Enter your email'),
      '#description'=>t('Please enter email.')
    );

    $form['submit']=array(
        '#type'=>'submit',
        '#value'=>t('Submit')
      );

  return $form;
}
