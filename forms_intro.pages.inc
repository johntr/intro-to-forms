<?php
/**
 * Implements hook_form().
 */
function forms_intro_form($node, &$form_state) {

  $form = array();

  $form['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact us.'),
    '#description' => t('If you would like to contact us. Please enter your info below.')
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
      '#description'=>t('Please enter email.'),
      '#required' => TRUE
        );

    $form['contact']['country']=array(
            '#type'=>'select',
            '#title'=>t('Select your country'),
            '#options'=>array('Canada','Mexico','UK','USA'),
            '#default_value' => 3
        );

    $form['contact']['body']=array(
      '#type'=>'textarea',
      '#title'=>t('Message'),
      '#description'=>t('Please enter your message here.')
        );

    $form['submit']=array(
        '#type'=>'submit',
        '#value'=>t('Submit')
        );

  return $form;
}

/**
 * Implements hook_form().
 */
function forms_intro_form_validate($form, &$form_state) {

  if(filter_var($form_state['values']['email'], FILTER_VALIDATE_EMAIL) == false) {
    form_set_error('email','Email field does not contain a vaild email address');
  }

  return $form;
}
